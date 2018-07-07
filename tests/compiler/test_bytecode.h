#pragma once

#include <stdlib.h>
#include <string.h>
#include "../common.h"
#include "../../src/compiler/bytecode.h"

// effect: frees the list of str.
// return: whether the string generated from the instructions matched the supplied string.
bool eq_bytecode_exp(Bytecode *instrs, char *expected) {
    char *str = to_string(instrs);
    bool eq = strcmp(str, expected) == 0;
    free(str);
    free_bytecode(instrs);
    return eq;
}

// Tests appending to an empty list.
bool test_bytecode_append_empty() {
    Bytecode *instrs = empty();
    append('a', instrs);
    return eq_bytecode_exp(instrs, "a");
}

// Tests appending to a populated list.
bool test_bytecode_append_populated() {
    Bytecode *instrs = empty();
    append('a', instrs);
    append('b', instrs);
    append('c', instrs);
    return eq_bytecode_exp(instrs, "abc");
}

// Tests two empty lists are equal.
bool test_bytecode_empty_eq() {
    Bytecode *i1 = empty();
    Bytecode *i2 = empty();
    return eq_bytecode(i1, i2);
}

// Tests two popuated lists are equal.
bool test_bytecode_populated_eq() {
    Bytecode *i1 = empty();
    append('a', i1);

    Bytecode *i2 = empty();
    append('a', i2);

    return eq_bytecode(i1, i2);
}

// Tests two lists are not equal if their length is different.
bool test_bytecode_len_not_eq() {
    Bytecode *i1 = empty();
    append('a', i1);
    Bytecode *i2 = empty();
    return !eq_bytecode(i1, i2);
}

// Tests two lists are different if the contain different instructions.
bool test_bytecode_contents_not_eq() {
    Bytecode *i1 = empty();
    append('a', i1);
    Bytecode *i2 = empty();
    append('b', i2);
    return !eq_bytecode(i1, i2);
}

// Runs all bytecode tests.
void test_bytecode(Ctx ctx) {
    Ctx bytecode_ctx = nested_ctx("bytecode", ctx);
    test(test_bytecode_append_empty(), "append empty", bytecode_ctx);
    test(test_bytecode_append_populated(), "append populated", bytecode_ctx);
    test(test_bytecode_empty_eq(), "empty eq", bytecode_ctx);
    test(test_bytecode_populated_eq(), "populated eq", bytecode_ctx);
    test(test_bytecode_contents_not_eq(), "contents not eq", bytecode_ctx);
}
