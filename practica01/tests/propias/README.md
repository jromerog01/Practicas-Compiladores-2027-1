# Pruebas propias del equipo — Práctica 1

## Uso

Cada archivo de `inputs/` debe ejecutarse con el programa `minic`. La salida estándar debe coincidir exactamente con el archivo del mismo nombre ubicado en `expected/`, cambiando la extensión `.mc` por `.out`.

Ejemplo:

```text
./minic tests/propias/inputs/t06_varios_digitos.mc
```

Estas pruebas son independientes de las públicas (`tests/public/`), pensadas para no depender únicamente de los ejemplos ya proporcionados con la práctica (sección 12 de la especificación).

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
