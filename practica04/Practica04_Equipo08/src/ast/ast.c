#include "ast/ast.h"

void ast_node_list_init(ASTNodeList *list) {
    if (list == NULL) {
        return;
    }

    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

int ast_node_list_append(ASTNodeList *list, ASTNode *node) {
    /* TODO: validar argumentos. */
    /* TODO: crecer el arreglo sin perder el anterior si realloc falla. */
    /* TODO: transferir la propiedad de node sólo cuando la inserción funcione. */
    (void)list;
    (void)node;
    return 0;
}

void ast_node_list_destroy(ASTNodeList *list) {
    /* TODO: destruir cada nodo contenido. */
    /* TODO: liberar el arreglo interno y dejar la lista vacía. */
    (void)list;
}

ASTNode *ast_create_program(
    ASTNodeList statements,
    size_t line,
    size_t column
) {
    /* TODO: construir la raíz y adquirir statements sólo si hay éxito. */
    (void)statements;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_block(
    ASTNodeList statements,
    size_t line,
    size_t column
) {
    /* TODO: construir el bloque y adquirir statements sólo si hay éxito. */
    (void)statements;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_variable_declaration(
    ASTDeclaredType declared_type,
    const char *name,
    ASTNode *initializer,
    size_t line,
    size_t column
) {
    /* TODO: copiar name y aplicar el contrato de propiedad a initializer. */
    (void)declared_type;
    (void)name;
    (void)initializer;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_assignment(
    const char *name,
    ASTNode *value,
    size_t line,
    size_t column
) {
    /* TODO: copiar name y aplicar el contrato de propiedad a value. */
    (void)name;
    (void)value;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_print(
    ASTNode *expression,
    size_t line,
    size_t column
) {
    /* TODO: construir el nodo y aplicar el contrato a expression. */
    (void)expression;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_if(
    ASTNode *condition,
    ASTNode *then_branch,
    ASTNode *else_branch,
    size_t line,
    size_t column
) {
    /* TODO: conservar condition, then_branch y el else opcional. */
    (void)condition;
    (void)then_branch;
    (void)else_branch;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_while(
    ASTNode *condition,
    ASTNode *body,
    size_t line,
    size_t column
) {
    /* TODO: construir el ciclo con su condición y cuerpo. */
    (void)condition;
    (void)body;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_binary(
    BinaryOperator operator,
    ASTNode *left,
    ASTNode *right,
    size_t line,
    size_t column
) {
    /* TODO: construir el operador y adquirir ambos operandos sólo si hay éxito. */
    (void)operator;
    (void)left;
    (void)right;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_unary(
    UnaryOperator operator,
    ASTNode *operand,
    size_t line,
    size_t column
) {
    /* TODO: construir el operador y adquirir operand sólo si hay éxito. */
    (void)operator;
    (void)operand;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_identifier(
    const char *name,
    size_t line,
    size_t column
) {
    /* TODO: copiar name; no conservar el apuntador del token. */
    (void)name;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_integer(
    const char *lexeme,
    size_t line,
    size_t column
) {
    /* TODO: copiar el lexema completo del entero. */
    (void)lexeme;
    (void)line;
    (void)column;
    return NULL;
}

ASTNode *ast_create_boolean(
    int value,
    size_t line,
    size_t column
) {
    /* TODO: normalizar y conservar el valor booleano. */
    (void)value;
    (void)line;
    (void)column;
    return NULL;
}


void ast_destroy(ASTNode *node) {
    /* TODO: aceptar NULL y liberar recursivamente según node->type. */
    (void)node;
}

