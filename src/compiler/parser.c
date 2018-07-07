#include "lexer.h"
#include "bytecode.h"
#include "../common/codes.h"
#include <stdlib.h>

static void expr(Bytecode *instrs, Tokens *input);

// effect: prints an error message detailing the expected token and actual
//         parsed from the input stream. Also exits the program.
static void err_expected(TokenType type, Token actual) {
    printf("Expected ");
    print_token_type(type);
    printf(" but got ");
    print_token(actual);
    printf("\n");
    exit(0);
}

// effect: asserts that the lookahead token has the same type as expected.
//         If so the lookahead is consumed. Otherwise an error is thrown.
static void expect(TokenType exp_type, Tokens *input) {
    Token next = lookahead(input);
    if (next.type == exp_type) {
        consume(input);
    }
    else {
        err_expected(exp_type, next);
    }
}

// effect: parses an integer and appends a push instruction to the bytecode.
//         Outputs an error if the lookahead is not an integer.
static void num(Bytecode *instrs, Tokens *input) {
    Token t = lookahead(input);
    switch (t.type) {
        case INT:
            append_push(t.int_val, instrs);
            consume(input);
            break;
        default:
            err_expected(INT, t);
            break;
    }
}

// effect: parses an expression in parenthesis, or a number. Appends the
//         instructions for either to the bytecode.
//         Outputs an error if the lookahead is incorrect.
static void factor(Bytecode *instrs, Tokens *input) {
    Token t = lookahead(input);
    switch (t.type) {
        case INT:
            num(instrs, input);
            break;
        case OPEN_PAREN:
            consume(input);
            expr(instrs, input);
            expect(CLOSE_PAREN, input);
            break;
        default:
            err_expected(OPEN_PAREN, t);
            break;
    }
}

// effect: appends either an add or subtract instruction to the bytecode.
static void append_binop(BinOp op, Bytecode *instrs) {
    char code;
    switch (op) {
        case PLUS:
            code = ADD_CODE;
            break;
        case SUB:
            code = SUB_CODE;
            break;
        case MULT:
            code = MULT_CODE;
            break;
        case DIV:
            code = DIV_CODE;
            break;
    }
    append(code, instrs);
}

// effect: parses a '*' or '/' operation, and pushes the operation to the
//         bytecode. Outputs an error if parsing fails.
static void term(Bytecode *instrs, Tokens *input) {
    factor(instrs, input);

    while (1) {
        Token t = lookahead(input);

        if (t.type == BIN_OP && (t.bin_op == MULT || t.bin_op == DIV)) {
            consume(input);
            factor(instrs, input);
            append_binop(t.bin_op, instrs);
        }
        else {
            break;
        }
    }
}

// effect: parses a '+' or '-' operation, and pushes the operation to the
//         bytecode. Outputs an error if parsing fails.
static void expr(Bytecode *instrs, Tokens *input) {
    term(instrs, input);

    while (1) {
        Token t = lookahead(input);

        if (t.type == BIN_OP && (t.bin_op == PLUS || t.bin_op == SUB)) {
            consume(input);
            term(instrs, input);
            append_binop(t.bin_op, instrs);
        }
        else {
            break;
        }
    }
}

// effect: parses the input and produces bytecode to calculate the result.
void parse(Bytecode *instrs, Tokens *input) {
    expr(instrs, input);

    Token t = lookahead(input);
    if (t.type == DONE) {
        append(HALT_CODE, instrs);
    }
    else {
        err_expected(HALT_CODE, t);
    }
}
