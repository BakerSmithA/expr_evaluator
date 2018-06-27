SRC = src
OUT = out

BIN = $(OUT)/eval

MAIN = $(SRC)/main.c
FILES = $(MAIN)

default:
	gcc-7 $(FILES) -o $(BIN)
