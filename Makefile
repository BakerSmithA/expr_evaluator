SRC = src
TESTS = tests
OUT = out

CC = gcc
CFLAGS = -Wall -Wextra

# Common
INPUT = $(SRC)/common/input.c
COMMON = $(INPUT)

# Compiler
CMP_DIR = $(SRC)/compiler

CMP_BYTECODE = $(CMP_DIR)/bytecode.c
CMP_TOKEN = $(CMP_DIR)/token.c
CMP_LEXER = $(CMP_DIR)/lexer.c
CMP_PARSER = $(CMP_DIR)/parser.c

CMP_FILES = $(COMMON) $(CMP_BYTECODE) $(CMP_TOKEN) $(CMP_LEXER) $(CMP_PARSER)
CMP_MAIN = $(CMP_FILES) $(SRC)/compiler/main.c
CMP_BIN = $(OUT)/comp

TEST_CMP = $(CMP_FILES) $(TESTS)/compiler/test_compiler.c

# Stack Machine
VM_MAIN = $(COMMON) $(SRC)/vm/main.c
VM_BIN = $(OUT)/vm

TEST_VM = $(TESTS)/vm/test_vm.c

.PHONY : compiler vm

all: compiler vm

compiler:
	$(CC) $(CFLAGS) $(CMP_MAIN) -o $(CMP_BIN)

vm:
	$(CC) $(CFLAGS) $(VM_MAIN) -o $(VM_BIN)

test_compiler:
	$(CC) $(CFLAGS) $(TEST_CMP) -o $(CMP_BIN)
	./$(CMP_BIN)

test_vm:
	$(CC) $(CFLAGS) $(TEST_VM) -o $(VM_BIN)
	./$(VM_BIN)

test: test_compiler test_vm

clean:
	rm $(OUT)/*
