#include "lexer.h"
#include "bytecode.h"

// effect: prints an error message detailing the expected token and actual
//         parsed from the input stream. Also exits the program.
void err_expected_type(TokenType type, Token actual) {
    printf("Expected ");
    print_token_type(type);
    printf(" but got ");
    print_token(actual);
    printf("\n");
    exit(0);
}

// effect: prints an error message detailing the expected token and actual
//         parsed from the input stream. Also exits the program.
void err_expected_token(Token expected, Token actual) {
    printf("Expected ");
    print_token(expected);
    printf(" but got ");
    print_token(actual);
    printf("\n");
    exit(0);
}

// effect: asserts that the lookahead token has the same type as the expected
//         token. If so the next is consumed. Otherwise an error is thrown.
void expect(Token expected, Tokens *input) {
    Token next = lookahead(input);
    if (next.type == expected.type) {
        consume(input);
    }
    else {
        err_expected_token(expected, next);
    }
}

// effect: parses an integer and appends a push instruction to the bytecode.
//         Outputs an error if the lookahead is not an integer.
void term(Bytecode *instrs, Tokens *input) {
    Token t = lookahead(input);
    switch (t.type) {
        case INT:
            append_push(t.int_val, instrs);
            consume(input);
            break;
        default:
            err_expected_type(INT, t);
            break;
    }
}

// effect: parses an expression in parenthesis, or a number. Appends the
//         instructions for either to the bytecode.
//         Outputs an error if the lookahead is incorrect.
void factor(Bytecode *instrs, Tokens *input) {
    expect(open_paren(), input);
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
    term(instrs, input);
    while (1) {
        Token t = lookahead(input);

        if (t.type == BIN_OP) {
            consume(input);
            term(instrs, input);
            append_binop(t.bin_op, instrs);
        }
        else if (t.type == DONE) {
            break;
        }
        else {
            err_expected_type(BIN_OP, t);
            break;
        }
    }
    append_halt(instrs);
}
