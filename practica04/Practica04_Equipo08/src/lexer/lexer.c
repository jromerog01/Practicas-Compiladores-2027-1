#include "lexer/lexer.h"
#include "lexer/token.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int simple_token_type(int c, TokenType *type) {
    if (type == NULL) {
        return 0;
    }

    switch (c) {
        case '+':
            *type = PLUS;
            return 1;
        case '-':
            *type = MINUS;
            return 1;
        case '*':
            *type = STAR;
            return 1;
        case '/':
            *type = SLASH;
            return 1;
        case '=':
            *type = ASSIGN;
            return 1;
        case '<':
            *type = LESS;
            return 1;
        case '>':
            *type = GREATER;
            return 1;
        case '(':
            *type = LPAREN;
            return 1;
        case ')':
            *type = RPAREN;
            return 1;
        case '{':
            *type = LBRACE;
            return 1;
        case '}':
            *type = RBRACE;
            return 1;
        case ';':
            *type = SEMICOLON;
            return 1;
        default:
            return 0;
    }
}

int compound_token_type(int first, int second, TokenType *type) {
    if (type == NULL) {
        return 0;
    }

    if (second == '=') {
        switch (first) {
            case '=':
                *type = EQUAL;
                return 1;
            case '!':
                *type = NOT_EQUAL;
                return 1;
            case '<':
                *type = LESS_EQUAL;
                return 1;
            case '>':
                *type = GREATER_EQUAL;
                return 1;
            default:
                break;
        }
    }

    if (first == '&' && second == '&') {
        *type = AND;
        return 1;
    }

    if (first == '|' && second == '|') {
        *type = OR;
        return 1;
    }

    return 0;
}

static int is_ignored_space(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static int is_digit_char(int c) {
    return isdigit(c) != 0;
}

static int is_identifier_start(int c) {
    return isalpha(c) != 0 || c == '_';
}

static int is_identifier_part(int c) {
    return isalnum(c) != 0 || c == '_';
}

static void advance_position(int c, size_t *line, size_t *column) {
    if (c == '\n' || c == '\r') {
        (*line)++;
        *column = 0;
    } else {
        (*column)++;
    }
}

static int peek_char(FILE *file) {
    int c = fgetc(file);

    if (c != EOF) {
        ungetc(c, file);
    }

    return c;
}

static char *scan_lexeme(FILE *file, int first, int (*accepts)(int), size_t *column) {
    size_t capacity = 8;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int c;

    if (buffer == NULL) {
        return NULL;
    }

    buffer[length++] = (char)first;

    while ((c = fgetc(file)) != EOF && accepts(c)) {
        (*column)++;
        if (length + 1 >= capacity) {
            char *grown;
            capacity *= 2;
            grown = realloc(buffer, capacity);

            if (grown == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = grown;
        }
        buffer[length++] = (char)c;
    }

    if (c != EOF) {
        ungetc(c, file);
    }

    buffer[length] = '\0';
    return buffer;
}

static void skip_line_comment(FILE *file, size_t *column) {
    int c;

    while ((c = fgetc(file)) != EOF && c != '\n' && c != '\r') {
        (*column)++;
    }

    if (c != EOF) {
        ungetc(c, file);
    }
}

// NOTE: Entregar en vez de imprimir (eliminar los emit...)

/* Construye el token en 'out'. No imprime nada */
static LexerStatus make_token(Token *out, TokenType type, const char *lexeme,
                              size_t line, size_t column) {
    if (!token_init(out, type, lexeme, line, column)) {
        return LEXER_STATUS_MEMORY_ERROR;
    }
    return LEXER_STATUS_OK;
}

static LexerStatus scan_identifier(FILE *file, int first, size_t *column,
                                   size_t line, size_t token_column,
                                   Token *out) {
    char *lexeme = scan_lexeme(file, first, is_identifier_part, column);
    LexerStatus status;

    if (lexeme == NULL) {
        return LEXER_STATUS_MEMORY_ERROR;
    }

    status = make_token(out, token_keyword_type(lexeme), lexeme,
                        line, token_column);
    free(lexeme);
    return status;
}

static LexerStatus scan_integer(FILE *file, int first, size_t *column,
                                size_t line, size_t token_column,
                                Token *out) {
    char *lexeme = scan_lexeme(file, first, is_digit_char, column);
    LexerStatus status;

    if (lexeme == NULL) {
        return LEXER_STATUS_MEMORY_ERROR;
    }

    status = make_token(out, INTEGER, lexeme, line, token_column);
    free(lexeme);
    return status;
}

int lexer_init(Lexer *lexer, FILE *source) {
    if (lexer == NULL || source == NULL) {
        return 0;
    }

    lexer->source = source;
    lexer->line = 1;
    lexer->column = 0;
    return 1;
}

/* El lexer no reserva memoria propia ni cierra el archivo */
void lexer_destroy(Lexer *lexer) {
    if (lexer != NULL) {
        lexer->source = NULL;
    }
}

LexerStatus lexer_next_token(Lexer *lexer, Token *out) {
    FILE *file;
    int c;

    if (lexer == NULL || lexer->source == NULL || out == NULL) {
        return LEXER_STATUS_IO_ERROR;
    }

    file = lexer->source;

    while ((c = fgetc(file)) != EOF) {
        size_t token_line;
        size_t token_column;
        TokenType type;
        int next;

        if (c == '\r') {
            int after = fgetc(file);
            if (after != '\n' && after != EOF) {
                ungetc(after, file);
            }
        }

        token_line = lexer->line;
        token_column = lexer->column;
        advance_position(c, &lexer->line, &lexer->column);

        if (is_ignored_space(c)) {
            continue;
        }

        if (c == '/' && peek_char(file) == '/') {
            fgetc(file);
            lexer->column++;
            skip_line_comment(file, &lexer->column);
            continue;
        }

        if (is_identifier_start(c)) {
            return scan_identifier(file, c, &lexer->column,
                                   token_line, token_column, out);
        }

        if (is_digit_char(c)) {
            return scan_integer(file, c, &lexer->column,
                                token_line, token_column, out);
        }

        next = peek_char(file);
        if (compound_token_type(c, next, &type)) {
            char lexeme[3];

            fgetc(file);
            lexer->column++;
            lexeme[0] = (char)c;
            lexeme[1] = (char)next;
            lexeme[2] = '\0';

            return make_token(out, type, lexeme, token_line, token_column);
        }

        if (!simple_token_type(c, &type)) {
            type = ERROR;
        }

        {
            char lexeme[2] = {(char)c, '\0'};

            return make_token(out, type, lexeme, token_line, token_column);
        }
    }

    if (ferror(file)) {
        return LEXER_STATUS_IO_ERROR;
    }

    return make_token(out, TOKEN_EOF, "", lexer->line, lexer->column);
}
