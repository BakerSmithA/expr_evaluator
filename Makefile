SRC = src
OUT = out

CC = gcc
CFLAGS = -Wall -Wextra

COMPILER_MAIN = $(SRC)/compiler/main.c
COMPILER_BIN = $(OUT)/comp

# Stack Machine
SM_MAIN = $(SRC)/stack_machine/main.c
SM_BIN = $(OUT)/sm

.PHONY : compiler sm

all: compiler sm

compiler:
	$(CC) $(CFLAGS) $(COMPILER_MAIN) -o $(COMPILER_BIN)

sm:
	$(CC) $(CFLAGS) $(SM_MAIN) -o $(SM_BIN)

clean:
	rm $(OUT)/*
