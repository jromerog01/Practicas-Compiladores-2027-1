#ifndef MINIC_LEXER_H
#define MINIC_LEXER_H

#include "token.h"

#include <stdio.h>

/* Estado que el lexer conserva. El lexer solo lo lee */
typedef struct {
    FILE *source;
    size_t line;
    size_t column;
} Lexer;

/*
   Un caracter no reconocido NO es un fallo, porque se entrega como token ERROR
   con LEXER_STATUS_OK. Y ya los otros estados son fallos internos
*/
typedef enum {
    LEXER_STATUS_OK,
    LEXER_STATUS_IO_ERROR,
    LEXER_STATUS_MEMORY_ERROR
} LexerStatus;

int simple_token_type(int c, TokenType *type);
int compound_token_type(int first, int second, TokenType *type);
int lexer_init(Lexer *lexer, FILE *source);

/*
   Con LEXER_STATUS_OK out recibe un token nuevo que su propiedad
   pasa a quien llama, que debe liberarlo co token_destroy.
   Con otro estado, out no contiene un token válido
*/
LexerStatus lexer_next_token(Lexer *lexer, Token *out);

void lexer_destroy(Lexer *lexer);

#endif
