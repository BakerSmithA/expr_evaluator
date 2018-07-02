#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "../common/codes.h"

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

// return: whether the two lists of contain the same instruction codes.
bool eq_bytecode(Bytecode *instrs1, Bytecode *instrs2) {
    if (instrs1->len != instrs2->len) {
        return false;
    }

    bool eq = true;
    for (Instr *i1=instrs1->first, *i2=instrs2->first; i1!=NULL && eq; i1=i1->next, i2=i2->next) {
        eq = i1->code == i2->code;
    }

    return eq;
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

// effect: frees all the nodes in the list, and the reference to the list.
void free_bytecode(Bytecode *instrs) {
    for (Instr *instr=instrs->first; instr!=NULL;) {
        Instr *old = instr;
        instr = instr->next;
        free(old);
    }
    free(instrs);
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
//         Then appends the operand in the next byte.
void append_push(int num, Bytecode *instrs) {
    append(PUSH_CODE, instrs);
    append((char)num, instrs);
}

// effect: appends an add instruction to the end of the list of instructions.
void append_add(Bytecode *instrs) {
    append(ADD_CODE, instrs);
}

// effect: appends a sub instruction to the end of the list of instructions.
void append_sub(Bytecode *instrs) {
    append(SUB_CODE, instrs);
}

// effect: appends a halt operation to the end of the list of instructions.
void append_halt(Bytecode *instrs) {
    append(HALT_CODE, instrs);
}
