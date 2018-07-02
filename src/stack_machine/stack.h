#pragma once

#include <stdlib.h>

// An element in the stack.
typedef struct StackNode {
    int val;
    struct StackNode *below;
} StackNode;

// Stack of integer values.
typedef struct {
    StackNode *top;
} Stack;

// return: an empty stack.
Stack* empty() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    *stack = (Stack){ .top=NULL };
    return stack;
}

// effect: frees the stack, and all nodes in the stack.
void free_stack(Stack *stack) {
    for (StackNode *n=stack->top; n!=NULL;) {
        StackNode *old = n;
        n = n->below;
        free(old);
    }
    free(stack);
}

// effect: adds a value to the top of the stack.
void push(int val, Stack *stack) {
    StackNode *node = (StackNode*)malloc(sizeof(StackNode));
    *node = (StackNode){ .val=val, .below=stack->top };

    stack->top = node;
}

// effect: removes the value from the top of the stack and returns it.
int pop(Stack *stack) {
    int val = stack->top->val;
    stack->top = stack->top->below;
    return val;
}

// effect: takes the top value x and value below the top y and performs the
//         supplied binary operation ~ s.t. x~y. The result of the binary op
//         is pushed to the top of the stack.
void bin_op(int(*op)(int, int), Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);
    int r = op(x, y);
    push(r, stack);
}

int _add(int x, int y) {
    return x + y;
}

int _sub(int x, int y) {
    return x - y;
}

// effect: adds the top two values on top of the stack and pushes the result.
void add(Stack *stack) {
    bin_op(_add, stack);
}

// effect: subtracts the value below the top from the top value, and pushes the result.
void sub(Stack *stack) {
    bin_op(_sub, stack);
}
