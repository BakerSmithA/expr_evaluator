SRC = src
OUT = out

COMPILER_BIN = $(OUT)/comp
COMPILER = $(SRC)/compiler/main.c

compiler:
	gcc -Wall -Wextra $(COMPILER) -o $(COMPILER_BIN)

clean:
	rm $(OUT)/*
