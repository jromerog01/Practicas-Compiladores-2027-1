#ifndef MINIC_AST_PRINTER_H
#define MINIC_AST_PRINTER_H

#include "ast/ast.h"

/*
   Imprime en stdout el nodo recibido y sus descendientes con el formato
   canonico de la Practica 4: un elemento por linea y exactamente dos
   espacios por nivel de profundidad.

   No imprime el encabezado "AST:" ni el mensaje final del programa; eso
   es responsabilidad de main.
*/
void ast_print(const ASTNode *node);

#endif