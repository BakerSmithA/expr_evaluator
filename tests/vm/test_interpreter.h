#pragma once

#include "../common.h"
#include "../../src/vm/interpreter.h"

// Tests interpreting a push command.
bool test_inter_push() {
    char bytecode[3] = { PUSH_CODE, 0x05, HALT_CODE };
    Interpreter *inter = new_interpreter(bytecode);
    int r = interpret(inter);
    free_interpreter(inter);
    return r == 5;
}

// Tests interpreting an add command.
bool test_inter_add() {
    char bytecode[6] = { PUSH_CODE, 0x05, PUSH_CODE, 0x03, ADD_CODE, HALT_CODE };
    Interpreter *inter = new_interpreter(bytecode);
    int r = interpret(inter);
    free_interpreter(inter);
    return r == 8;
}

// Tests interpreting a sub command.
bool test_inter_sub() {
    char bytecode[6] = { PUSH_CODE, 0x05, PUSH_CODE, 0x03, SUB_CODE, HALT_CODE };
    Interpreter *inter = new_interpreter(bytecode);
    int r = interpret(inter);
    free_interpreter(inter);
    return r == 2;
}

// Runs all bytecode tests.
void test_interpreter(Ctx ctx) {
    Ctx inter_ctx = nested_ctx("interpreter", ctx);
    test(test_inter_push(), "push", inter_ctx);
    test(test_inter_add(), "add", inter_ctx);
    test(test_inter_sub(), "sub", inter_ctx);
}
