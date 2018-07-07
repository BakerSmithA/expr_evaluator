#pragma once

#include "../common/codes.h"
#include "stack.h"

typedef struct Interpreter Interpreter;

// return: a new interpreter allocated on the heap.
Interpreter *new_interpreter(char *bytecode);

// effect: frees the interpreter, and the stack it contains. The bytecode given
//         to the interpreter is **not** freed.
void free_interpreter(Interpreter *inter);

// return: the result at the top of the stack after interpreting the bytecode.
int interpret(Interpreter *inter);
