#pragma once

#include "../common.h"
#include "../../src/compiler/lexer.h"

// Tests the lookahead token is correctly set when creating a list of tokens from a string.
bool test_from_string() {
    return false;
}

// Runs all bytecode tests.
void test_lexer(Ctx ctx) {
    Ctx lexer_ctx = nested_ctx("lexer", ctx);
    test(test_from_string(), "from string", lexer_ctx);
}
