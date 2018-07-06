#pragma once

#include "../common.h"
#include "../../src/compiler/parser.h"

// Tests a single term is parsed from the start of the input stream.
bool test_parses_single_num() {
    Bytecode *expected = empty();
    append_push(10, expected);
    append_halt(expected);

    Tokens *ts = from_string("10");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Tests parsing a single binary operator.
bool test_single_binary_op() {
    Bytecode *expected = empty();
    append_push(7, expected);
    append_push(5, expected);
    append_add(expected);
    append_halt(expected);

    Tokens *ts = from_string("7+5");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Tests parsing a multiple binary operators.
bool test_multiple_binary_op() {
    Bytecode *expected = empty();
    append_push(7, expected);
    append_push(5, expected);
    append_add(expected);
    append_push(3, expected);
    append_sub(expected);
    append_halt(expected);

    Tokens *ts = from_string("7+5-3");
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
    append_add(expected);
    append_add(expected);
    append_halt(expected);

    Tokens *ts = from_string("(1)+(2+3)");
    Bytecode *actual = empty();
    parse(actual, ts);
    free_tokens(ts);

    return eq_bytecode(actual, expected);
}

// Runs all parser tests.
void test_parser(Ctx ctx) {
    Ctx parser_ctx = nested_ctx("parser", ctx);
    test(test_parses_single_num(), "single num", parser_ctx);
    test(test_single_binary_op(), "single binary op", parser_ctx);
    test(test_multiple_binary_op(), "multiple binary op", parser_ctx);
    test(test_parses_parens(), "parenthesis", parser_ctx);
}
