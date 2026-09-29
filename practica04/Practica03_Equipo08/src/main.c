#include "lexer/lexer.h"
#include "parser/parser.h"

#include <stdio.h>


/*
   Códigos de salida: 0 programa valido, 1 errores en el archivo fuente,
   2 uso incorrecto, archivo que no se pudo abrir o fallo interno
*/
int main(int argc, char **argv) {
    FILE *file;
    Lexer lexer;
    Parser parser;
    int valid;
    int exit_code;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo.mc>\n", argv[0]);
        return 2;
    }

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: no se pudo abrir '%s'.\n", argv[1]);
        return 2;
    }

    lexer_init(&lexer, file);
    parser_init(&parser, &lexer);

    valid = parser_parse_program(&parser);

    if (parser.internal_failure) {
        exit_code = 2;
    } else if (valid) {
        printf("Programa sintacticamente correcto.\n");
        exit_code = 0;
    } else {
        exit_code = 1;
    }

    parser_destroy(&parser);
    lexer_destroy(&lexer);
    fclose(file);

    return exit_code;
}
