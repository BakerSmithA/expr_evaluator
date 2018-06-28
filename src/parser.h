#include "lexer.h"
#include "bytecode.h"

// effect: prints an error message detailing the expected token and actual
//         parsed from the input stream. Also exits the program.
void err_expected(char *expected, Token actual) {
    printf("Expected %s but got ", expected);
    print_token(actual);
    printf("\n");
    exit(0);
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
            err_expected("integer", t);
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
            err_expected("binary op", t);
            break;
        }
    }
}
