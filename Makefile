SRC = src
TESTS = tests
OUT = out

CC = gcc
CFLAGS = -Wall -Wextra

# Compiler
COMPILER_MAIN = $(SRC)/compiler/main.c
COMPILER_BIN = $(OUT)/comp

TEST_COMPILER = $(TESTS)/compiler/test_compiler.c
TEST_VM = $(TESTS)/vm/test_vm.c

# Stack Machine
VM_MAIN = $(SRC)/vm/main.c
VM_BIN = $(OUT)/vm

.PHONY : compiler vm

all: compiler vm

compiler:
	$(CC) $(CFLAGS) $(COMPILER_MAIN) -o $(COMPILER_BIN)

vm:
	$(CC) $(CFLAGS) $(VM_MAIN) -o $(VM_BIN)

test_compiler:
	$(CC) $(CFLAGS) $(TEST_COMPILER) -o $(COMPILER_BIN)
	./$(COMPILER_BIN)

test_vm:
	$(CC) $(CFLAGS) $(TEST_VM) -o $(VM_BIN)
	./$(VM_BIN)

test: test_compiler test_vm

clean:
	rm $(OUT)/*
