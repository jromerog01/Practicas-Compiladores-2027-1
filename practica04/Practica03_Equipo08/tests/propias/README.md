# Pruebas propias Práctica 3

Cada caso corresponde a un punto de la lista mínima de la sección 20 del PDF

## Uso

Desde la raíz del proyecto:

```text
sh tests/propias/run_own_tests.sh ./minic
```

También se ejecutan con `make test`, después de las pruebas públicas

## Convención

- `validos/*.mc`: el programa debe terminar con código `0`, imprimir
  `Programa sintacticamente correcto.` en `stdout` y no escribir en `stderr`
- `invalidos/*.mc`: el programa debe terminar con código `1`, no escribir en
  `stdout`, y su `stderr` debe ser idéntico al archivo `.err` del mismo nombre

## Casos válidos

| Entrada | Caso |
|---|---|
| `v01_archivo_vacio.mc` | Archivo vacío. |
| `v02_declaracion_sin_inicializacion.mc` | Una declaración sin inicialización. |
| `v03_declaracion_con_inicializacion.mc` | Una declaración con inicialización. |
| `v04_varias_declaraciones.mc` | Varias declaraciones. |
| `v05_asignaciones.mc` | Asignaciones. |
| `v06_expresion_aritmetica.mc` | Expresiones aritméticas. |
| `v07_precedencia_suma_multiplicacion.mc` | Precedencia entre suma y multiplicación. |
| `v08_parentesis.mc` | Paréntesis en expresiones. |
| `v09_relacionales.mc` | Operadores relacionales. |
| `v10_igualdad.mc` | Operadores de igualdad. |
| `v11_logicos.mc` | Operadores lógicos. |
| `v12_unario_negativo.mc` | Operador unario negativo. |
| `v13_print.mc` | Sentencias `print`. |
| `v14_if_sin_else.mc` | Condicionales sin `else`. |
| `v15_if_con_else.mc` | Condicionales con `else`. |
| `v16_if_anidados.mc` | Condicionales anidados |
| `v17_asociacion_else.mc` | Asociación del `else` con el `if` más cercano |
| `v18_while.mc` | Ciclos `while` |
| `v19_bloques_vacios.mc` | Bloques vacíos |
| `v20_bloque_varias_sentencias.mc` | Bloques con varias sentencias |
| `v21_estructuras_anidadas.mc` | Estructuras anidadas |

## Casos inválidos

| Entrada | Caso |
|---|---|
| `e01_falta_punto_y_coma.mc` | Ausencia de punto y coma. |
| `e02_falta_parentesis.mc` | Ausencia de paréntesis. |
| `e03_falta_llave.mc` | Ausencia de llaves. |
| `e04_expresion_incompleta.mc` | Expresiones incompletas. |
| `e05_operador_sin_operandos.mc` | Operadores sin operandos. |
| `e06_token_inesperado.mc` | Tokens inesperados (`else` sin `if`). |
| `e07_error_lexico.mc` | Error léxico recibido por el parser, sin diagnóstico sintáctico. |
| `e08_multiples_errores.mc` | Múltiples errores en el mismo archivo. |
| `e09_recuperacion.mc` | Recuperación después de errores dentro y fuera de un bloque |
| `e10_contenido_despues_de_sentencia.mc` | Contenido después de una sentencia válida |
| `e11_eof_inesperado.mc` | Verificación de `TOKEN_EOF` al faltar una sentencia |
