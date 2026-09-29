# Práctica 3

## Información general

| Campo | Información |
|---|---|
| Asignatura | Compiladores |
| Número de práctica | 3 |
| Equipo | Equipo 08 |

## Integrantes

| Nombre completo | Número de cuenta | Correo electrónico |
|---|---|---|
| Gael Emiliano Arreguin Salgado | 321121721 | emiliano.arreguin@ciencias.unam.mx |
| Jesus Antonio Romero Godoy | 321144292 | jromerog@ciencias.unam.mx |

## Estructura del proyecto


```
text
Practica03_EquipoXX/
├── README.md
├── CHANGELOG.md
├── reporte.pdf
├── Makefile
├── include/
│   ├── lexer/    (lexer.h, token.h)
│   └── parser/   (parser.h)
├── src/
│   ├── main.c
│   ├── lexer/    (lexer.c, token.c)
│   └── parser/   (parser.c)
└── tests/
    ├── public/   (pruebas públicas de P3)
    ├── propias/  (pruebas del equipo)
    └── lexer/    (pruebas de P1 y P2)
```

### Módulos implementados

| Módulo | Responsabilidad |
|---|---|
| src/main.c | Valida argumentos, abre el archivo, coordina lexer y parser y muestra el resultado |
| lexer/ | Tokens y analizador léxico; entrega un token por llamada ya sin imprimirlo |
| parser/ | Parser descendente recursivo, diagnósticos y recuperación frente a errores. Robusto |

## Compilación

```
text
make
make clean
```

## Ejecución


```
text
./minic programa.mc
```

## Funcionalidades implementadas

- [x] Interfaz incremental del lexer
- [x] Declaraciones, asignaciones, print, if/else, while y bloques.
- [x] Expresiones con precedencia y asociatividad.
- [x] Diagnósticos léxicos y sintácticos con línea y columna.
- [x] Recuperación ante errores por sentencias.
- [x] Verificación de TOKEN_EOF.

## Pruebas

```
text
make test
```

Ejecuta las 17 pruebas públicas y las 32 propias. Ver tests/README.md

## Problemas

> Estuvo retadora la práctica...
