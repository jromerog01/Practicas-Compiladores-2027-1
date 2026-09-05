CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude
TARGET = minic

SRC = src/main.c src/lexer/lexer.c src/lexer/token.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

test: $(TARGET)
	@fail=0; \
	shopt -s nullglob; \
	for f in tests/public/inputs/*.mc; do \
		base=$$(basename "$$f" .mc); \
		exp="tests/public/expected/$$base.out"; \
		if [ -f "$$exp" ]; then \
			out=$$(./$(TARGET) "$$f"); \
			if [ "$$out" = "$$(cat "$$exp")" ]; then \
				echo "PASS: $$f"; \
			else \
				echo "FAIL: $$f"; \
				fail=1; \
			fi; \
		fi; \
	done; \
	if [ $$fail -eq 0 ]; then echo "Todas las pruebas pasaron (o no hay pruebas aun)."; else exit 1; fi
