#pragma once

#include <stdlib.h>

// Stack of integer values.
typedef struct Stack Stack;

// return: an empty stack.
Stack* empty();

// effect: frees the stack, and all nodes in the stack.
void free_stack(Stack *stack);

// effect: adds a value to the top of the stack.
void push(int val, Stack *stack);

// effect: removes the value from the top of the stack and returns it.
int pop(Stack *stack);

// effect: adds the top two values on top of the stack and pushes the result.
void stk_add(Stack *stack);

// effect: subtracts the value below the top from the top value, and pushes the result.
void stk_sub(Stack *stack);

// effect: multiplies the top two values on top of the stack and pushes the result.
void stk_mult(Stack *stack);

// effect: divides the value below the top from the top value, and pushes the result.
void stk_div(Stack *stack);
