#include "interpreter.h"
#include "../common/codes.h"
#include "stack.h"

struct Interpreter {
    // Code to run.
    char *bytecode;
    // Instruction pointer.
    int instr_ptr;
    // Used to compute.
    Stack *stack;
};

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
static char curr_code(Interpreter *inter) {
    return inter->bytecode[inter->instr_ptr];
}

// effect: interprets a push instruction by pushing the operand onto the stack.
static void interpret_push(Interpreter *inter) {
    inter->instr_ptr += 1; // Move to read the operand.
    char operand = curr_code(inter);
    push(operand, inter->stack);
}

// effect: interprets an add instruction by adding the top two values.
static void interpret_add(Interpreter *inter) {
    stk_add(inter->stack);
}

// effect: interprets a subtraction instruction by subtracting the top two values.
static void interpret_sub(Interpreter *inter) {
    stk_sub(inter->stack);
}

// effect: interprets a multiply instruction by multiplying the top two values.
static void interpret_mult(Interpreter *inter) {
    stk_mult(inter->stack);
}

// effect: interprets a division instruction by dividing the top two values.
static void interpret_div(Interpreter *inter) {
    stk_div(inter->stack);
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
            case MULT_CODE:
                interpret_mult(inter);
                break;
            case DIV_CODE:
                interpret_div(inter);
                break;
        }
        inter->instr_ptr += 1;
    }

    return pop(inter->stack);
}
