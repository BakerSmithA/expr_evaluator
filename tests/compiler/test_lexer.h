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
bool test_lex_plus_op() {
    return test_lex_op("+", PLUS);
}

// Tests parsing a minus operator.
bool test_lex_minus_op() {
    return test_lex_op("-", SUB);
}

// Tests parsing a multiplication operator.
bool test_lex_mult_op() {
    return test_lex_op("*", MULT);
}

// Tests parsing a division operator.
bool test_lex_div_op() {
    return test_lex_op("/", DIV);
}

// Tests parsing an integer.
bool test_lex_integer() {
    Tokens *ts = from_string("12");
    bool r = lookahead(ts).type == INT && lookahead(ts).int_val == 12;
    free_tokens(ts);
    return r;
}

// Tests parsing an open parenthesis.
bool test_lex_open_paren() {
    Tokens *ts = from_string("(");
    bool r = lookahead(ts).type == OPEN_PAREN;
    free_tokens(ts);
    return r;
}

// Tests parsing a closing parenthesis.
bool test_lex_close_paren() {
    Tokens *ts = from_string(")");
    bool r = lookahead(ts).type == CLOSE_PAREN;
    free_tokens(ts);
    return r;
}

// Tests consume moves onto the next token.
bool test_lex_consume() {
    Tokens *ts = from_string("1+2");
    consume(ts);
    bool r = lookahead(ts).type == BIN_OP && lookahead(ts).bin_op == PLUS;
    free_tokens(ts);
    return r;
}

// Tests any spaces between tokens is ignored.
bool test_ignores_spaces() {
    return test_lex_op("    +", PLUS);
}

// Tests any tabs between tokens is ignored.
bool test_ignores_tabs() {
    return test_lex_op("\t\t+", PLUS);
}

// Runs all bytecode tests.
void test_lexer(Ctx ctx) {
    Ctx lexer_ctx = nested_ctx("lexer", ctx);
    test(test_lex_plus_op(), "plus", lexer_ctx);
    test(test_lex_minus_op(), "minus", lexer_ctx);
    test(test_lex_mult_op(), "mult", lexer_ctx);
    test(test_lex_div_op(), "div", lexer_ctx);
    test(test_lex_integer(), "integer", lexer_ctx);
    test(test_lex_open_paren(), "open paren", lexer_ctx);
    test(test_lex_close_paren(), "close paren", lexer_ctx);
    test(test_lex_consume(), "consume", lexer_ctx);
    test(test_ignores_spaces(), "ignores spaces", lexer_ctx);
    test(test_ignores_tabs(), "ignores tabs", lexer_ctx);
}
