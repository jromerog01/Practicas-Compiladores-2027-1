#ifndef MINIC_PARSER_H
#define MINIC_PARSER_H

#include "lexer/lexer.h"

/* 
   Aquí el parser tiene 'current' y 'previous'  y los libera con token_destroy,
   'previous' cada vez que avanza y ambos en parser_destroy
*/
typedef struct {
    Lexer *lexer;
    Token current;
    Token previous;         /* ultimo token consumido */
    int had_error;          /* hubo al menos un error léxico o sintáctico */
    int panic_mode;         /* ya se reportó un error sobre el actual */
    int internal_failure;   /* el lexer no pudo entregar un token */
} Parser;

void parser_init(Parser *parser, Lexer *lexer);

/* Analiza el archivo completo y devuelve 1 si el programa es valido */
int parser_parse_program(Parser *parser);

void parser_destroy(Parser *parser);

#endif
