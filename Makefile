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
CMP_TEST = $(CMP_FILES) $(TESTS)/compiler/test_compiler.c
CMP_BIN = $(OUT)/comp

# Stack Machine
VM_DIR = $(SRC)/vm

VM_STACK = $(VM_DIR)/stack.c
VM_INTERPRETER = $(VM_DIR)/interpreter.c
VM_FILES = $(COMMON) $(VM_STACK) $(VM_INTERPRETER)

VM_MAIN = $(VM_FILES) $(SRC)/vm/main.c
VM_TEST = $(VM_FILES) $(TESTS)/vm/test_vm.c
VM_BIN = $(OUT)/vm

.PHONY : compiler vm

all: compiler vm

compiler:
	$(CC) $(CFLAGS) $(CMP_MAIN) -o $(CMP_BIN)

vm:
	$(CC) $(CFLAGS) $(VM_MAIN) -o $(VM_BIN)

test_compiler:
	$(CC) $(CFLAGS) $(CMP_TEST) -o $(CMP_BIN)
	./$(CMP_BIN)

test_vm:
	$(CC) $(CFLAGS) $(VM_TEST) -o $(VM_BIN)
	./$(VM_BIN)

test: test_compiler test_vm

clean:
	rm $(OUT)/*
