#pragma once

#include "../common.h"
#include "../../src/compiler/lexer.h"

// Tests parsing a binary operation.
bool test_lex_op(char *input, BinOp expected_op) {
    Tokens *ts = from_string(input);
    bool r = lookahead(ts).type == BIN_OP && lookahead(ts).bin_op == expected_op;
    free_tokens(ts);
    return r;
}

// Tests parsing a plus operator.
bool test_plus_op() {
    return test_lex_op("+", PLUS);
}

// Tests parsing a minus operator.
bool test_minus_op() {
    return test_lex_op("-", SUB);
}

// Tests parsing an integer.
bool test_integer() {
    Tokens *ts = from_string("12");
    bool r = lookahead(ts).type == INT && lookahead(ts).int_val == 12;
    free_tokens(ts);
    return r;
}

// Tests consume moves onto the next token.
bool test_consume() {
    Tokens *ts = from_string("1+2");
    consume(ts);
    bool r = lookahead(ts).type == BIN_OP && lookahead(ts).bin_op == PLUS;
    free_tokens(ts);
    return r;
}

// Runs all bytecode tests.
void test_lexer(Ctx ctx) {
    Ctx lexer_ctx = nested_ctx("lexer", ctx);
    test(test_plus_op(), "plus", lexer_ctx);
    test(test_minus_op(), "minus", lexer_ctx);
    test(test_integer(), "integer", lexer_ctx);
    test(test_consume(), "consume", lexer_ctx);
}
