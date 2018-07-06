#pragma once

#include "../common.h"
#include "../../src/compiler/parser.h"

// Tests a single term is parsed from the start of the input stream.
bool test_parses_single_num() {
    Bytecode *expected = empty();
    append_push(10, expected);
    append_op(HALT_CODE, expected);

    Tokens *ts = from_string("10");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Tests parsing a single + or - operator.
bool test_single_binary_low_precedence() {
    Bytecode *expected = empty();
    append_push(7, expected);
    append_push(5, expected);
    append_op(ADD_CODE, expected);
    append_op(HALT_CODE, expected);

    Tokens *ts = from_string("7+5");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Tests parsing a multiple + or - operators.
bool test_multiple_binary_low_precedence() {
    Bytecode *expected = empty();
    append_push(7, expected);
    append_push(5, expected);
    append_op(ADD_CODE, expected);
    append_push(3, expected);
    append_op(SUB_CODE, expected);
    append_op(HALT_CODE, expected);

    Tokens *ts = from_string("7+5-3");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Tests parsing single * or / operator.
bool test_single_binary_high_precedence() {
    Bytecode *expected = empty();
    append_push(7, expected);
    append_push(5, expected);
    append_op(MULT_CODE, expected);
    append_op(HALT_CODE, expected);

    Tokens *ts = from_string("7*5");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Tests parsing single * or / operator.
bool test_multiple_binary_high_precedence() {
    Bytecode *expected = empty();
    append_push(7, expected);
    append_push(5, expected);
    append_op(MULT_CODE, expected);
    append_push(3, expected);
    append_op(DIV_CODE, expected);
    append_op(HALT_CODE, expected);

    Tokens *ts = from_string("7*5/3");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Tests a mix of precedence operators.
bool test_parses_mixed_precedence() {
    Bytecode *expected = empty();
    append_push(7, expected);
    append_push(5, expected);
    append_push(3, expected);
    append_op(MULT_CODE, expected);
    append_op(ADD_CODE, expected);
    append_op(HALT_CODE, expected);

    Tokens *ts = from_string("7+5*3");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Tests parsing parenthesis.
bool test_parses_parens() {
    Bytecode *expected = empty();
    append_push(1, expected);
    append_push(2, expected);
    append_push(3, expected);
    append_op(ADD_CODE, expected);
    append_op(MULT_CODE, expected);
    append_op(HALT_CODE, expected);

    Tokens *ts = from_string("(1)*(2+3)");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Runs all parser tests.
void test_parser(Ctx ctx) {
    Ctx parser_ctx = nested_ctx("parser", ctx);
    test(test_parses_single_num(), "single num", parser_ctx);
    test(test_single_binary_low_precedence(), "single + or -", parser_ctx);
    test(test_multiple_binary_low_precedence(), "multiple + or -", parser_ctx);
    test(test_single_binary_high_precedence(), "single * or /", parser_ctx);
    test(test_multiple_binary_high_precedence(), "multiple * or /", parser_ctx);
    test(test_parses_mixed_precedence(), "mixed precedence", parser_ctx);
    test(test_parses_parens(), "parenthesis", parser_ctx);
}
