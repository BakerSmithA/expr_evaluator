#include <string.h>
#include "../common.h"
#include "../../src/compiler/bytecode.h"

// return: whether the string generated from the instructions matched the supplied string.
bool eq_bytecode(Bytecode *instrs, char *expected) {
    char *str = to_string(instrs);
    bool eq = strcmp(str, expected) == 0;
    free(str);
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
void test_bytecode() {
    context("bytecode");
    test(test_append_empty(), "append empty");
    test(test_append_populated(), "append populated");
}
