#pragma once

#include "../common.h"
#include "../../src/vm/stack.h"

// Tests pushing then popping a value to the stack.
bool test_stack_push_pop() {
    Stack *stack = empty();

    push(2, stack);
    int r = pop(stack);

    free_stack(stack);
    return r == 2;
}

// Tests adding the top two values on the stack.
bool test_stack_add() {
    Stack *stack = empty();

    push(2, stack);
    push(3, stack);
    add(stack);
    int r = pop(stack);

    free_stack(stack);
    return r == 5;
}

// Tests subtracting the top two values on the stack.
bool test_stack_sub() {
    Stack *stack = empty();

    push(5, stack);
    push(2, stack);
    sub(stack);
    int r = pop(stack);

    free_stack(stack);
    return r == 3;
}

// Runs all bytecode tests.
void test_stack(Ctx ctx) {
    Ctx stack_ctx = nested_ctx("stack", ctx);
    test(test_stack_push_pop(), "push/pop", stack_ctx);
    test(test_stack_add(), "add", stack_ctx);
    test(test_stack_sub(), "sub", stack_ctx);
}
