CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude
TARGET = minic

SRC = src/main.c src/lexer/lexer.c src/lexer/token.c src/parser/parser.c \
      src/ast/ast.c src/ast/ast_printer.c
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
	@sh tests/public/run_public_tests.sh ./$(TARGET)
	@sh tests/propias/run_own_tests.sh ./$(TARGET)
