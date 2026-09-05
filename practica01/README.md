# Práctica 1 — Infraestructura básica del analizador léxico

## Información general

| Campo | Información |
|---|---|
| Asignatura | Compiladores |
| Número de práctica | 1 |
| Equipo | Equipo XX |

## Integrantes

| Nombre completo                    | Número de cuenta | Correo electrónico                 |
|------------------------------------|------------------|------------------------------------|
| Gael Emiliano Arreguin Salgado     | 321121721        | emiliano.arreguin@ciencias.unam.mx |
| Jesus Antonio Romero Godoy         | 321144292        | jromerog@ciencias.unam.mx          |

## Estructura del proyecto

```text
practica01/
├── README.md
├── CHANGELOG.md
├── reporte.pdf
├── Makefile
├── include/
│   └── lexer/
│       ├── lexer.h
│       └── token.h
├── src/
│   ├── main.c
│   └── lexer/
│       ├── lexer.c
│       └── token.c
└── tests/
    ├── README.md
    ├── public/
    │   ├── README.md
    │   ├── inputs/
    │   └── expected/
    └── propias/
        ├── README.md
        ├── inputs/
        └── expected/
```

### Módulos implementados

| Archivo o módulo | Responsabilidad |
|---|---|
| `src/main.c` | Punto de entrada: valida los argumentos de línea de comandos, abre el archivo fuente, invoca al analizador léxico, muestra los resultados y libera los recursos utilizados. |
| `include/lexer/token.h`, `src/lexer/token.c` | Sistema de tokens: enumeración `TokenType`, estructura `Token`, creación (`token_init`), impresión en el formato de salida (`token_print`) y liberación de memoria (`token_destroy`). |
| `include/lexer/lexer.h`, `src/lexer/lexer.c` | Analizador léxico: seguimiento de línea y columna (incluyendo `\n`, `\r` y `\r\n`), manejo de espacios en blanco, reconocimiento de símbolos simples (`simple_token_type`), enteros (`scan_integer`), generación de `ERROR` para caracteres no reconocidos y de `TOKEN_EOF` al terminar el archivo. |

## Requisitos

- GCC con soporte para C11.
- GNU Make.

## Compilación

```text
make
```

Para eliminar los archivos generados:

```text
make clean
```

## Ejecución

```text
./minic programa.mc
```

## Funcionalidades implementadas

- [x] Lectura del archivo fuente.
- [x] Sistema de tokens.
- [x] Seguimiento de línea y columna.
- [x] Manejo de espacios en blanco.
- [x] Símbolos simples.
- [x] Números enteros.
- [x] Caracteres no reconocidos mediante `ERROR`.
- [x] Final del archivo mediante `TOKEN_EOF`.

## Pruebas

```text
make test
```

Compila el ejecutable si hace falta y corre dos conjuntos de pruebas con la misma convención (`inputs/*.mc` + `expected/*.out`):

- `tests/public/`: 10 casos mínimos proporcionados con la práctica.
- `tests/propias/`: 13 casos escritos por el equipo, uno por cada punto mínimo de la sección 12 de la especificación (archivo vacío, solo espacios, un único token, todos los símbolos simples, entero de un dígito, entero de varios dígitos, varios tokens en una línea, tokens en varias líneas, combinación de espacios y tabuladores, un carácter no reconocido, varios caracteres no reconocidos, posición correcta de línea/columna, y detección correcta de fin de archivo).

El detalle de cada caso está documentado en `tests/public/README.md` y `tests/propias/README.md`.

## Problemas conocidos
> no se conocen problemas adicionales a las limitaciones propias del alcance de la Práctica 1.
