# Changelog



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
