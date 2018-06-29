#pragma once

#include <stdlib.h>

// Stack machine instructions:
//
// |-------------|------------|-----------------------------------------------|
// | Instruction | Code       | Description                                   |
// |-------------|------------|-----------------------------------------------|
// | Push        | 000 XXXXX  | Push the 5-bit number to the top of the stack |
// | Add         | 001 00000  | Add the two values at the top of the stack    |
// | Sub         | 010 00000  | Subtract the value below the top of the stack |
// |             |            | from the element at the top                   |
// |-------------|------------|-----------------------------------------------|

// Binary codes for each operation.
unsigned char _PUSH_CODE = 0x1F; // F so can be ANDed with the operand.
unsigned char _ADD_CODE  = 0x20;
unsigned char _SUB_CODE  = 0x40;

// A single bytecode instruction.
typedef struct Instr {
    unsigned char code;
    struct Instr *next;
} Instr;

// effect: prints the bits of the instruction code.
void print_instr(Instr instr) {
    for (int i=0; i<8; i++) {
        printf("%d", !!((instr.code << i) & 0x80));
    }
}

// List of bytecode instructions.
typedef struct {
    Instr *first;
    Instr *last;
    int len;
} Bytecode;

// Useful for iterating through all instructions in bytecode.
#define foreach_instr(instr, instrs) for (instr=instrs->first; instr!=NULL; instr=instr->next)

// effect: prints all the instructions in the list of instructions.
void print_bytecode(Bytecode *instrs) {
    Instr *i;
    foreach_instr(i, instrs) {
        print_instr(*i);
        printf("\n");
    }
}

// effect: writes all the instructions to a file.
void write_bytecode(Bytecode *instrs, FILE *fp) {
    Instr *i;
    foreach_instr(i, instrs) {
        print_instr(*i);
        printf("\n");
        int resp = fputc(i->code, fp);

        if (resp != i->code) {
            printf("Error occured while outputting file");
        }
    }
}

// effect: allocates a string and writes the instruction codes to the string.
char* to_string(Bytecode *instrs) {
    char *s = malloc(sizeof(char) * instrs->len + 1);
    int i=0;
    Instr *instr;
    foreach_instr(instr, instrs) {
        s[i] = instr->code;
        i++;
    }
    s[i] = '\0';
    return s;
}

// effect: returns an empty list of bytecode instructions.
Bytecode* empty() {
    Bytecode *instrs = (Bytecode*)malloc(sizeof(Bytecode));
    *instrs = (Bytecode){ .first=NULL, .last=NULL, .len=0 };
    return instrs;
}

// effect: adds a new instruction to the end of list of instructions.
void append(char code, Bytecode *instrs) {
    Instr *instr = (Instr*)malloc(sizeof(Instr));
    *instr = (Instr){ .code=code, .next=NULL };

    if (instrs->last != NULL) {
        instrs->last->next = instr;
    }
    if (instrs->first == NULL) {
        instrs->first = instr;
    }
    instrs->last = instr;
    instrs->len += 1;
}

// effect: appends a push instruction to the end of the list of instructions.
void append_push(int num, Bytecode *instrs) {
    unsigned char code = _PUSH_CODE & ((unsigned char)num);
    append(code, instrs);
}

// effect: appends an add instruction to the end of the list of instructions.
void append_add(Bytecode *instrs) {
    append(_ADD_CODE, instrs);
}

// effect: appends a sub instruction to the end of the list of instructions.
void append_sub(Bytecode *instrs) {
    append(_SUB_CODE, instrs);
}
