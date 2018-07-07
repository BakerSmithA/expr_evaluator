#pragma once

#include "../common.h"
#include "../../src/vm/interpreter.h"

bool test_inter_op(int n1, int n2, char op_code, int expected) {
    char bytecode[] = { PUSH_CODE, n1, PUSH_CODE, n2, op_code, HALT_CODE };
    Interpreter *inter = new_interpreter(bytecode);
    int r = interpret(inter);
    free_interpreter(inter);
    return r == expected;
}

// Tests interpreting a push command.
bool test_inter_push() {
    char bytecode[] = { PUSH_CODE, 0x05, HALT_CODE };
    Interpreter *inter = new_interpreter(bytecode);
    int r = interpret(inter);
    free_interpreter(inter);
    return r == 5;
}

// Tests interpreting an add command.
bool test_inter_add() {
    return test_inter_op(5, 3, ADD_CODE, 8);
}

// Tests interpreting a sub command.
bool test_inter_sub() {
    return test_inter_op(5, 3, SUB_CODE, 2);
}

// Tests interpreting a multiply command.
bool test_inter_mult() {
    return test_inter_op(5, 3, MULT_CODE, 15);
}

// Tests interpreting a division command.
bool test_inter_div() {
    return test_inter_op(8, 2, DIV_CODE, 4);
}

// Runs all bytecode tests.
void test_interpreter(Ctx ctx) {
    Ctx inter_ctx = nested_ctx("interpreter", ctx);
    test(test_inter_push(), "push", inter_ctx);
    test(test_inter_add(), "add", inter_ctx);
    test(test_inter_sub(), "sub", inter_ctx);
    test(test_inter_mult(), "mult", inter_ctx);
    test(test_inter_div(), "div", inter_ctx);
}
