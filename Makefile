SRC = src
OUT = out

BIN = $(OUT)/eval

MAIN = $(SRC)/main.c

default:
	gcc -Wall $(MAIN) -o $(BIN)
