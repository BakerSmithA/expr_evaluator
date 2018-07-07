#pragma once

#include <stdbool.h>
#include <stdio.h>

// A single bytecode instruction.
typedef struct Instr Instr;

// effect: prints the bits of the instruction code.
void print_instr(Instr instr);

// List of bytecode instructions.
typedef struct Bytecode Bytecode;

// effect: prints all the instructions in the list of instructions.
void print_bytecode(Bytecode *instrs);

// effect: writes all the instructions to a file.
void write_bytecode(Bytecode *instrs, FILE *fp);

// return: whether the two lists of contain the same instruction codes.
bool eq_bytecode(Bytecode *instrs1, Bytecode *instrs2);

// effect: allocates a string and writes the instruction codes to the string.
char* to_string(Bytecode *instrs);

// effect: returns an empty list of bytecode instructions.
Bytecode* empty();

// effect: frees all the nodes in the list, and the reference to the list.
void free_bytecode(Bytecode *instrs);

// effect: adds a new instruction to the end of list of instructions.
void append(char code, Bytecode *instrs);

// effect: appends a push instruction to the end of the list of instructions.
//         Then appends the operand in the next byte.
void append_push(int num, Bytecode *instrs);
