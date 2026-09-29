#include "parser/parser.h"

#include <stdio.h>

/*
   Reporta que se esperaba 'expected' y se encontro 'token'. Y si ya se reportó
   un error sobre el token actual (panic_mode), ya no se repite
*/
static void syntax_error(Parser *parser, const Token *token, const char *expected) {
    if (parser->panic_mode || parser->internal_failure) {
        return;
    }

    parser->panic_mode = 1;
    parser->had_error = 1;

    if (token->type == TOKEN_EOF) {
        fprintf(stderr, "Error sintactico [%zu:%zu]: se esperaba %s, "
                "pero se encontro TOKEN_EOF.\n",
                token->line, token->column, expected);
    } else {
        fprintf(stderr, "Error sintactico [%zu:%zu]: se esperaba %s, "
                "pero se encontro '%s'.\n",
                token->line, token->column, expected, token->lexeme);
    }
}

/*
   Consume current y pide el siguiente token al lexer.
   Un token ERROR se reporta como error léxico, luego se libera y se pide otro, luego
   el resto del parser nunca lo ve, asi que no genera error sintáctico. Luego si el
   lexer falla, 'current' pasa a ser un TOKEN_EOF sin lexema para
   que todas las producciones terminen 'normal'
*/
static void advance(Parser *parser) {
    LexerStatus status;

    if (parser->internal_failure) {
        return;
    }
    token_destroy(&parser->previous);
    parser->previous = parser->current;
    parser->panic_mode = 0;

    for (;;) {
        status = lexer_next_token(parser->lexer, &parser->current);

        if (status != LEXER_STATUS_OK) {
            parser->internal_failure = 1;
            parser->had_error = 1;
            parser->current.type = TOKEN_EOF;
            parser->current.lexeme = NULL;

            if (status == LEXER_STATUS_MEMORY_ERROR) {
                fprintf(stderr, "Error: memoria insuficiente.\n");
            } else {
                fprintf(stderr, "Error: no se pudo leer el archivo fuente.\n");
            }
            return;
        }

        if (parser->current.type != ERROR) {
            return;
        }

        parser->had_error = 1;
        fprintf(stderr, "Error lexico [%zu:%zu]: caracter no reconocido '%s'.\n",
                parser->current.line, parser->current.column,
                parser->current.lexeme);
        token_destroy(&parser->current);
    }
}

static int check(const Parser *parser, TokenType type) {
    return parser->current.type == type;
}

/* FIXME: Debe consumir el token */
static int match(Parser *parser, TokenType type) {
    if (!check(parser, type)) {
        return 0;
    }

    advance(parser);
    return 1;
}

/*
   Si no está, reporta el error y devuelve 0 sin consumir nada ni fingir que el 
   token estaba presente
*/
static int consume(Parser *parser, TokenType expected, const char *description) {
    if (match(parser, expected)) {
        return 1;
    }

    syntax_error(parser, &parser->current, description);
    return 0;
}

// NOTE: La sección 13

/* Sincronización por sentencias */
static void synchronize(Parser *parser) {
    for (;;) {
        switch (parser->current.type) {
            case SEMICOLON:
                advance(parser);    // se consume y sigue otra sentencia
                return;
            case INT:
            case BOOL:
            case IF:
            case WHILE:
            case PRINT:
            case IDENTIFIER:
            case LBRACE:    // no se consume
            case RBRACE:
            case ELSE:
            case TOKEN_EOF: // los procesa la estructura exterior 
                return;
            default:
                advance(parser);
        }
    }
}

void parser_init(Parser *parser, Lexer *lexer) {
    parser->lexer = lexer;
    parser->current.type = TOKEN_EOF;
    parser->current.lexeme = NULL;
    parser->previous.type = TOKEN_EOF;
    parser->previous.lexeme = NULL;
    parser->had_error = 0;
    parser->panic_mode = 0;
    parser->internal_failure = 0;
    advance(parser); // primer token de anticipacion
}

void parser_destroy(Parser *parser) {
    token_destroy(&parser->current);
    token_destroy(&parser->previous);
}

static int parse_statement(Parser *parser);
static int parse_expression(Parser *parser);

// NOTE: Empiezan los statement

/*
   statement hasta el 'terminator' (TOKEN_EOF en el programa, RBRACE en un
   bloque) Cada vuelta consume al menos un token o sincroniza
*/
static void parse_statement_list(Parser *parser, TokenType terminator) {
    while (!check(parser, terminator) && !check(parser, TOKEN_EOF)) {
        if (check(parser, RBRACE)) {
            // '}' sin bloque abierto
            syntax_error(parser, &parser->current, "una sentencia");
            advance(parser);
        } else if (!parse_statement(parser)) {
            synchronize(parser);
        }
    }
}

/* IDENTIFIER (ASSIGN expression) SEMICOLON */
static int parse_declaration(Parser *parser) {
    advance(parser);    // type INT o BOOL

    if (!consume(parser, IDENTIFIER, "un identificador")) {
        return 0;
    }

    if (match(parser, ASSIGN) && !parse_expression(parser)) {
        return 0;
    }

    return consume(parser, SEMICOLON, "';'");
}

/* IDENTIFIER ASSIGN expression SEMICOLON */
static int parse_assignment(Parser *parser) {
    advance(parser);    // IDENTIFIER ya verificado

    return consume(parser, ASSIGN, "'='")
        && parse_expression(parser)
        && consume(parser, SEMICOLON, "';'");
}

/* PRINT LPAREN expression RPAREN SEMICOLON */
static int parse_print_statement(Parser *parser) {
    advance(parser);    // PRINT ya verificado

    return consume(parser, LPAREN, "'('")
        && parse_expression(parser)
        && consume(parser, RPAREN, "')'")
        && consume(parser, SEMICOLON, "';'");
}

/* 
   IF LPAREN expression RPAREN statement ( ELSE statement )
   El if interior termina de analizarse antes que el exterior por lo que el
   ELSE queda asociado al if mas cercano sin rama else
*/
static int parse_if_statement(Parser *parser) {
    advance(parser);    // IF ya verificado

    if (!(consume(parser, LPAREN, "'('")
          && parse_expression(parser)
          && consume(parser, RPAREN, "')'")
          && parse_statement(parser))) {
        return 0;
    }

    if (match(parser, ELSE)) {
        return parse_statement(parser);
    }

    return 1;
}

/* WHILE LPAREN expression RPAREN statement */
static int parse_while_statement(Parser *parser) {
    advance(parser);    // WHILE ya verificado

    return consume(parser, LPAREN, "'('")
        && parse_expression(parser)
        && consume(parser, RPAREN, "')'")
        && parse_statement(parser);
}

/* LBRACE statement RBRACE */
static int parse_block(Parser *parser) {
    advance(parser);    // LBRACE ya verificado

    parse_statement_list(parser, RBRACE);
    return consume(parser, RBRACE, "'}'");
}

/* la producción se elige con el token de anticipacion. */
static int parse_statement(Parser *parser) {
    switch (parser->current.type) {
        case INT:
        case BOOL:
            return parse_declaration(parser);
        case IDENTIFIER:
            return parse_assignment(parser);
        case PRINT:
            return parse_print_statement(parser);
        case IF:
            return parse_if_statement(parser);
        case WHILE:
            return parse_while_statement(parser);
        case LBRACE:
            return parse_block(parser);
        default:
            syntax_error(parser, &parser->current, "una sentencia");
            if (check(parser, ELSE)) {
                advance(parser);    // 'else' sin 'if' se consume
            }
            return 0;
    }
}

/* primary ::= INTEGER | TRUE | FALSE | IDENTIFIER | LPAREN expression RPAREN */
static int parse_primary(Parser *parser) {
    if (match(parser, INTEGER) || match(parser, TRUE)
        || match(parser, FALSE) || match(parser, IDENTIFIER)) {
        return 1;
    }

    if (match(parser, LPAREN)) {
        return parse_expression(parser) && consume(parser, RPAREN, "')'");
    }

    syntax_error(parser, &parser->current, "una expresion");
    return 0;
}

/*
   unary_expression ::= MINUS unary_expression | primary
   La recur por la derecha da asociatividad derecha 
*/
static int parse_unary_expression(Parser *parser) {
    if (match(parser, MINUS)) {
        return parse_unary_expression(parser);
    }

    return parse_primary(parser);
}

/*
   NOTE: En los niveles binarios el ciclo ( op operando )* da asociatividad
   izquierda y cada nivel llama al siguiente de mayor precedencia
*/

/* multiplicative_expression ::= unary ( ( STAR | SLASH ) unary )* */
static int parse_multiplicative_expression(Parser *parser) {
    if (!parse_unary_expression(parser)) {
        return 0;
    }

    while (match(parser, STAR) || match(parser, SLASH)) {
        if (!parse_unary_expression(parser)) {
            return 0;
        }
    }

    return 1;
}

/* additive_expression ::= multiplicative ( ( PLUS | MINUS ) multiplicative )* */
static int parse_additive_expression(Parser *parser) {
    if (!parse_multiplicative_expression(parser)) {
        return 0;
    }

    while (match(parser, PLUS) || match(parser, MINUS)) {
        if (!parse_multiplicative_expression(parser)) {
            return 0;
        }
    }

    return 1;
}

/* comparison_expression ::= additive
       ( ( LESS | LESS_EQUAL | GREATER | GREATER_EQUAL ) additive )* */
static int parse_comparison_expression(Parser *parser) {
    if (!parse_additive_expression(parser)) {
        return 0;
    }

    while (match(parser, LESS) || match(parser, LESS_EQUAL)
           || match(parser, GREATER) || match(parser, GREATER_EQUAL)) {
        if (!parse_additive_expression(parser)) {
            return 0;
        }
    }

    return 1;
}

/* equality_expression ::= comparison ( ( EQUAL | NOT_EQUAL ) comparison )* */
static int parse_equality_expression(Parser *parser) {
    if (!parse_comparison_expression(parser)) {
        return 0;
    }

    while (match(parser, EQUAL) || match(parser, NOT_EQUAL)) {
        if (!parse_comparison_expression(parser)) {
            return 0;
        }
    }

    return 1;
}

/* and_expression ::= equality ( AND equality )* */
static int parse_and_expression(Parser *parser) {
    if (!parse_equality_expression(parser)) {
        return 0;
    }

    while (match(parser, AND)) {
        if (!parse_equality_expression(parser)) {
            return 0;
        }
    }

    return 1;
}

/* or_expression ::= and ( OR and )* */
static int parse_or_expression(Parser *parser) {
    if (!parse_and_expression(parser)) {
        return 0;
    }

    while (match(parser, OR)) {
        if (!parse_and_expression(parser)) {
            return 0;
        }
    }

    return 1;
}

/* expression ::= or_expression */
static int parse_expression(Parser *parser) {
    return parse_or_expression(parser);
}

/* program ::= statement_list TOKEN_EOF */
int parser_parse_program(Parser *parser) {
    parse_statement_list(parser, TOKEN_EOF);
    consume(parser, TOKEN_EOF, "el final del archivo");
    return !parser->had_error;
}
