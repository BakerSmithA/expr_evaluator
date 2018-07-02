#pragma once

#include "../common/codes.h"
#include "stack.h"

typedef struct {
    // Code to run.
    char *bytecode;
    // Instruction pointer.
    int instr_ptr;
    // Used to compute.
    Stack *stack;
} Interpreter;

// return: a new interpreter allocated on the heap.
Interpreter *new_interpreter(char *bytecode) {
    Interpreter *inter = (Interpreter*)malloc(sizeof(Interpreter));
    *inter = (Interpreter) { .bytecode=bytecode, .instr_ptr=0, .stack=empty() };
    return inter;
}

// effect: frees the interpreter, and the stack it contains. The bytecode given
//         to the interpreter is **not** freed.
void free_interpreter(Interpreter *inter) {
    free_stack(inter->stack);
    free(inter);
}

// return: the bytecode at the position of the instruction pointer.
char curr_code(Interpreter *inter) {
    return inter->bytecode[inter->instr_ptr];
}

// effect: interprets a push instruction by pushing the operand onto the stack.
void interpret_push(Interpreter *inter) {
    inter->instr_ptr += 1; // Move to read the operand.
    char operand = curr_code(inter);
    push(operand, inter->stack);
}

// effect: interprets an add instruction by adding the pop two values.
void interpret_add(Interpreter *inter) {
    add(inter->stack);
}

// effect: interprets a subtraction instruction by subtracting the pop two values.
void interpret_sub(Interpreter *inter) {
    sub(inter->stack);
}

// return: the result at the top of the stack after interpreting the bytecode.
int interpret(Interpreter *inter) {
    while (curr_code(inter) != HALT_CODE) {
        switch(curr_code(inter)) {
            case PUSH_CODE:
                interpret_push(inter);
                break;
            case ADD_CODE:
                interpret_add(inter);
                break;
            case SUB_CODE:
                interpret_sub(inter);
                break;
        }
        inter->instr_ptr += 1;
    }

    return pop(inter->stack);
}
