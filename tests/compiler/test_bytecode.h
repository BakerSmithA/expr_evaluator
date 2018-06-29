#pragma once

#include <string.h>
#include "../common.h"
#include "../../src/compiler/bytecode.h"

// effect: frees the list of instructions.
// return: whether the string generated from the instructions matched the supplied string.
bool eq_bytecode(Bytecode *instrs, char *expected) {
    char *str = to_string(instrs);
    bool eq = strcmp(str, expected) == 0;
    free(str);
    free_bytecode(instrs);
    return eq;
}

// Tests appending to an empty list.
bool test_append_empty() {
    Bytecode *instrs = empty();
    append('a', instrs);
    return eq_bytecode(instrs, "a");
}

// Tests appending to a populated list.
bool test_append_populated() {
    Bytecode *instrs = empty();
    append('a', instrs);
    append('b', instrs);
    append('c', instrs);
    return eq_bytecode(instrs, "abc");
}

// Runs all bytecode tests.
void test_bytecode(Ctx ctx) {
    Ctx bytecode_ctx = nested_ctx("bytecode", ctx);
    test(test_append_empty(), "append empty", bytecode_ctx);
    test(test_append_populated(), "append populated", bytecode_ctx);
}
