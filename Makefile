SRC = src
OUT = out

BIN = $(OUT)/eval

LEXER = $(SRC)/lexer.c
MAIN = $(SRC)/main.c
FILES = $(LEXER) $(MAIN)

default:
	gcc $(FILES) -o $(BIN)
