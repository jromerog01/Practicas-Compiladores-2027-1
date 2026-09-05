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

static int is_ignored_space(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static void advance_position(int c, size_t *line, size_t *column) {
    if (c == '\n' || c == '\r') {
        (*line)++;
        *column = 0;
    } else {
        (*column)++;
    }
}

static char *scan_integer(FILE *file, int first_digit, size_t *column) {
    size_t capacity = 8;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int c;

    if (buffer == NULL) {
        return NULL;
    }

    buffer[length++] = (char)first_digit;

    while ((c = fgetc(file)) != EOF && isdigit(c)) {
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


// Se encarga de leer el archivo caracter por caracter, y cuando termina de leer un lexema completo, crea el
// lexema, y lo imprime en la terminal
int lexer_scan(FILE *file) {
    size_t line = 1;
    size_t column = 0;
    int c;

    if (file == NULL) {
        return 2;
    }

    while ((c = fgetc(file)) != EOF) {
        size_t token_line = line;
        size_t token_column = column;
        TokenType type;

        // aqui resolvemos el '\r', para separar mejor las responsabilidades entre funciones,
        // primero revisamos si el siguiente caracter de '/r' es un '/n', y si lo es, lo consumimos aqui mismo
        if (c == '\r') {
            int next = fgetc(file);
            if (next != '\n' && next != EOF) {
                ungetc(next, file);
            }
        }

        advance_position(c, &line, &column);

        if (is_ignored_space(c)) {
            continue;
        }

        if (simple_token_type(c, &type)) {
            char lexeme[2] = {(char)c, '\0'};
            Token token;

            if (!token_init(&token, type, lexeme,
                            token_line, token_column)) {
                fprintf(stderr, "Error: no se pudo reservar memoria.\n");
                return 2;
            }

            token_print(&token);
            token_destroy(&token);
            continue;
        }

        if (isdigit(c)) {
            char *lexeme = scan_integer(file, c, &column);
            Token token;
            int ok;

            if (lexeme == NULL) {
                fprintf(stderr, "Error: no se pudo reservar memoria. \n");
                return 2;
            }

            ok = token_init(&token, INTEGER, lexeme, token_line, token_column);
            free(lexeme);

            if (!ok) {
                fprintf(stderr, "Error: no se pudo reservar memoria. \n");
                return 2;
            }

            token_print(&token);
            token_destroy(&token);
            continue;
        }
        {
            char lexeme[2] = {(char)c, '\0'};
            Token token;

            if (!token_init(&token, ERROR, lexeme, token_line, token_column)) {
                fprintf(stderr, "Error: no se pudo reservar memoria. \n");
                return 2;
            }

            token_print(&token);
            token_destroy(&token);
        }
    }

    if (ferror(file)) {
        fprintf(stderr, "Error: no se pudo leer el archivo.\n");
        return 2;
    }
    {
        Token token;

        if (!token_init(&token, TOKEN_EOF, "", line, column)) {
            fprintf(stderr, "Error: no se pudo reservar memoria. \n");
            return 2;
        }

        token_print(&token);
        token_destroy(&token);
    }
    return 0;
}
