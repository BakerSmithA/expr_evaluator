#pragma once

#include "../common.h"
#include "../../src/vm/stack.h"

// Tests applying a binary operation to the top two values on stack.
bool test_binop(void(op)(Stack*), int op1, int op2, int expected) {
    Stack *stack = empty();

    push(op1, stack);
    push(op2, stack);
    op(stack);
    int r = pop(stack);

    free_stack(stack);
    return r == expected;
}

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
    return test_binop(stk_add, 2, 3, 5);
}

// Tests subtracting the top two values on the stack.
bool test_stack_sub() {
    return test_binop(stk_sub, 5, 3, 2);
}

// Tests multiplying the top two values on the stack.
bool test_stack_mult() {
    return test_binop(stk_mult, 2, 3, 6);
}

// Tests dividing the top two values on the stack.
bool test_stack_div() {
    return test_binop(stk_div, 8, 2, 4);
}

// Runs all bytecode tests.
void test_stack(Ctx ctx) {
    Ctx stack_ctx = nested_ctx("stack", ctx);
    test(test_stack_push_pop(), "push/pop", stack_ctx);
    test(test_stack_add(), "add", stack_ctx);
    test(test_stack_sub(), "sub", stack_ctx);
    test(test_stack_mult(), "mult", stack_ctx);
    test(test_stack_div(), "div", stack_ctx);
}
