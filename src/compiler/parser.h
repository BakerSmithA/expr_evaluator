#include "lexer.h"
#include "bytecode.h"

void expr(Bytecode *instrs, Tokens *input);

// effect: prints an error message detailing the expected token and actual
//         parsed from the input stream. Also exits the program.
void err_expected(TokenType type, Token actual) {
    printf("Expected ");
    print_token_type(type);
    printf(" but got ");
    print_token(actual);
    printf("\n");
    exit(0);
}

// effect: asserts that the lookahead token has the same type as expected.
//         If so the lookahead is consumed. Otherwise an error is thrown.
void expect(TokenType exp_type, Tokens *input) {
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
void num(Bytecode *instrs, Tokens *input) {
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
void factor(Bytecode *instrs, Tokens *input) {
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
void append_binop(BinOp op, Bytecode *instrs) {
    switch (op) {
        case PLUS:
            append_add(instrs);
            break;
        case SUB:
            append_sub(instrs);
            break;
    }
}

// effect: parses a binary operation, and pushes the operation to the bytecode.
//         Outputs an error if parsing fails.
void expr(Bytecode *instrs, Tokens *input) {
    factor(instrs, input);

    while (1) {
        Token t = lookahead(input);

        if (t.type == BIN_OP) {
            consume(input);
            factor(instrs, input);
            append_binop(t.bin_op, instrs);
        }
        else if (t.type == DONE) {
            break;
        }
        else {
            break;
        }
    }
}

// effect: parses the input and produces bytecode to calculate the result.
void parse(Bytecode *instrs, Tokens *input) {
    expr(instrs, input);
    append_halt(instrs);
}
