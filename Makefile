SRC = src
OUT = out

BIN = $(OUT)/eval

MAIN = $(SRC)/main.c
FILES = $(MAIN)

default:
	gcc $(FILES) -o $(BIN)
