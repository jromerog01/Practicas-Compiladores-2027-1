# Pruebas propias — Práctica 2

## Uso

Cada archivo de `inputs/` debe ejecutarse con el programa `minic`. La salida estándar debe coincidir exactamente con el archivo del mismo nombre ubicado en `expected/`, cambiando la extensión `.mc` por `.out`.

Ejemplo:

```text
./minic tests/propias/inputs/t06_varios_digitos.mc
```

Estas pruebas son independientes de las públicas (`tests/public/`), pensadas para no depender únicamente de los ejemplos ya proporcionados con la práctica.

## Casos

| Entrada | Propósito principal |
|---|---|
| `t01_vacio.mc` | Archivo vacío. |
| `t02_solo_espacios.mc` | Archivo con únicamente espacios en blanco. |
| `t03_un_token.mc` | Un único token. |
| `t04_simbolos.mc` | Todos los símbolos simples, sin separadores. |
| `t05_un_digito.mc` | Número de un solo dígito. |
| `t06_varios_digitos.mc` | Número de varios dígitos. |
| `t07_varios_en_linea.mc` | Varios tokens en una sola línea. |
| `t08_varias_lineas.mc` | Tokens distribuidos en varias líneas. |
| `t09_tabs_espacios.mc` | Combinación de espacios y tabuladores entre tokens. |
| `t10_error_uno.mc` | Un carácter no reconocido y recuperación. |
| `t11_error_varios.mc` | Varios caracteres no reconocidos seguidos. |
| `t12_posicion.mc` | Posición correcta de línea y columna con indentación variable. |
| `t13_eof.mc` | Fin de archivo tras espacios/tabulador finales, sin salto de línea. |
| `t14_identificadores_basicos.mc` | Identificadores de uno y varios caracteres, con dígitos y guion bajo mezclados. |
| `t15_identificadores_con_digitos.mc` | Identificadores con dígitos después del primer carácter. |
| `t16_identificadores_guion_bajo.mc` | Identificadores formados solo o principalmente por guiones bajos. |
| `t17_todas_reservadas_orden_distinto.mc` | Las 8 palabras reservadas en un orden distinto al del PDF. |
| `t18_reservada_como_prefijo.mc` | Palabras reservadas como prefijo de un identificador más largo. |
| `t19_mayus_minus_palabra_reservada.mc` | Variantes de mayúsculas/minúsculas de una reservada, ninguna coincide. |
| `t20_booleanos_en_asignacion.mc` | Literales booleanos usados en declaración y asignación. |
| `t21_operador_asignacion.mc` | Operador de asignación simple. |
| `t22_igualdad_desigualdad.mc` | Operadores `==` y `!=`. |
| `t23_relacionales_simples.mc` | Operadores `<` y `>` sin componerse. |
| `t24_operadores_booleanos.mc` | Operadores `&&` y `||`. |
| `t25_operadores_incompletos.mc` | `!`, `&` y `|` aislados como errores, intercalados con identificadores. |
| `t26_comentarios_lineas_independientes.mc` | Dos comentarios en líneas propias antes de un token. |
| `t27_comentarios_despues_de_tokens.mc` | Comentario al final de dos líneas con código. |
| `t28_comentario_final_sin_salto.mc` | Comentario al final del archivo sin salto de línea final. |
| `t29_operador_division.mc` | Operador `/` distinto de comentario, en dos expresiones. |
| `t30_caracteres_no_reconocidos.mc` | Varios caracteres inválidos distintos, intercalados con identificadores. |
| `t31_multiples_errores_seguidos.mc` | Seis caracteres inválidos consecutivos sin recuperación intermedia. |
| `t32_linea_columna_indentacion.mc` | Seguimiento de columna con indentación creciente por línea. |
| `t33_espacios_y_lineas_vacias.mc` | Líneas vacías, espacios y tabulador combinados. |
| `t34_programa_completo.mc` | Programa MiniC completo con `if/else`, booleanos y operadores compuestos. |
