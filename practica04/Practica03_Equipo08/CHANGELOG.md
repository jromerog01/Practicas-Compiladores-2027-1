# Changelog

## [0.6.0] - 2026-09-21

### Agregado
- Parser descendente recursivo (parser.h, parser.c), o sea que valida la gramática de
  MiniC con precedencia de operadores, reporta errores en stderr y se recupera
  por sentencias
- Una interfaz incremental del lexer, usando nombres adecuados como lexer_init, lexer_next_token, lexer_destroy.
- Pruebas públicas de P3 y 32 pruebas propias del parser

### Cambiado
- El lexer ya no imprime tokens, ahora lexer_scan se reemplazó por lexer_next_token
- main.c coordina lexer y parser y devuelve 0, 1 o 2 de códigos e salida
- Las pruebas de P1 y P2 se movieron a tests/lexer/

## [0.5.0] - 2026-09-16

### Agregado
- Reconocimiento de identificadores (IDENTIFIER, exp. regular [a-zA-Z_][a-zA-Z0-9_]*) con máxima
  coincidencia.
- Clasificación de palabras reservadas con token_keyword_type en el módulo token, que
  justo compara el lexema completo contra las 8 palabras reservadas de MiniC. La comparación distingue
  mayúsculas de minúsculas y evita que un prefijo como while1 se reconozca como reservada.
- Literales booleanos true y false (TRUE, FALSE), dentro de la tabla de palabras reservadas.
- Operadores compuestos (==, !=, <=, >=, &&, ||) con compound_token_type y
  anticipación de un carácter
- Comentarios de una línea (//), que no generan tokens pero sí actualizan línea y columna
- 21 pruebas propias (t14–t34) y las pruebas públicas de la práctica 2, conservando las de la
  práctica 1

### Cambiado
- scan_integer se generalizó a scan_lexeme, que recibe un predicado de pertenencia al lexema y
  ahora usan tanto enteros como identificadores.
- La emisión de tokens se concentró en emit_token, así quitamos los cuatro bloques repetidos de
  token_init / token_print / token_destroy
- lexer_scan despacha en el orden de prioridad que nos dicta la sección 8 del PDF
- tests/propias/README.md indica los casos nuevos

## [0.4.0] - 2026-09-05

### Agregado
- 13 pruebas propias del equipo en `tests/propias/`, una por cada caso mínimo que se especifica
  en el PDF de la practica (archivo vacío, solo espacios, un único token, todos los símbolos simples,
  entero de un dígito, entero de varios dígitos, varios tokens en una línea, tokens en varias
  líneas, combinación de espacios y tabuladores, un carácter no reconocido, varios caracteres no
  reconocidos, posición correcta de línea/columna, y detección correcta de fin de archivo).
- `tests/README.md` y `tests/propias/README.md`, documentando ambos conjuntos de pruebas.
- `README.md` de entrega completado a partir de `PLANTILLA_README.md`.
- Este `CHANGELOG.md`.

### Cambiado
- Pruebas propias reorganizadas a `tests/propias/{inputs,expected}`, con la misma convención
  `inputs/*.mc` + `expected/*.out` que ya usaba `tests/public/`.
- La regla `test` del `Makefile` se simplificó a un solo bucle parametrizado por directorio que
  recorre `tests/propias` y `tests/public` con la misma lógica.

## [0.3.0] - 2026-09-05

### Agregado
- Reconocimiento de números enteros (`INTEGER`, patrón `[0-9]+`) en el analizador léxico.
- Generación del token `ERROR` para caracteres no reconocidos, con recuperación y continuación
  del análisis desde el carácter siguiente.
- Generación del token `TOKEN_EOF` con la posición correcta al finalizar el archivo (después de
  descontar espacios en blanco finales).

### Cambiado
- Seguimiento de línea y columna: `\r` aislado y la secuencia `\r\n` ahora se tratan como un único
  salto de línea (antes solo se manejaba `\n` de forma explícita).

## [0.2.0] - 2026-09-05

### Cambiado
- Se movió el contenido de `base-inicial/` (`include/`, `src/`, `Makefile`) a la raíz del
  proyecto, siguiendo la estructura mínima pedida para la practica.

## [0.1.0] - 2026-09-05

### Agregado
- Base inicial del proyecto: sistema de tokens completo (`include/lexer/token.h`,
  `src/lexer/token.c`), reconocimiento de los 12 símbolos simples de un carácter
  (`simple_token_type`), lectura y apertura del archivo fuente, validación de argumentos de línea
  de comandos.
