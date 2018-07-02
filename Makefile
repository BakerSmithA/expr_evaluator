SRC = src
TESTS = tests
OUT = out

CC = gcc
CFLAGS = -Wall -Wextra

# Compiler
COMPILER_MAIN = $(SRC)/compiler/main.c
COMPILER_BIN = $(OUT)/comp

TEST_COMPILER = $(TESTS)/compiler/test_compiler.c

# Stack Machine
SM_MAIN = $(SRC)/stack_machine/main.c
SM_BIN = $(OUT)/sm

.PHONY : compiler sm

all: compiler sm

compiler:
	$(CC) $(CFLAGS) $(COMPILER_MAIN) -o $(COMPILER_BIN)

sm:
	$(CC) $(CFLAGS) $(SM_MAIN) -o $(SM_BIN)

test_compiler:
	$(CC) $(CFLAGS) $(TEST_COMPILER) -o $(COMPILER_BIN)
	./$(COMPILER_BIN)

test: test_compiler

clean:
	rm $(OUT)/*
