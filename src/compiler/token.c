#include "token.h"
#include <stdio.h>

void print_binop(BinOp op) {
    switch (op) {
        case PLUS:
            printf("+");
            break;
        case SUB:
            printf("-");
            break;
        case MULT:
            printf("*");
            break;
        case DIV:
            printf("/");
            break;
    }
}

void print_token_type(TokenType type) {
    switch (type) {
        case INT: printf("int"); break;
        case BIN_OP: printf("binary op"); break;
        case OPEN_PAREN: printf("("); break;
        case CLOSE_PAREN: printf(")"); break;
        case DONE: printf("done"); break;
    }
}

// return: an integer token containing the given value.
Token integer(int val) {
    return (Token) { .type=INT, { .int_val=val } };
}

// return: a binary operation token of the given type.
Token bin_op(BinOp op) {
    return (Token) { .type=BIN_OP, { .bin_op=op } };
}

// return: a token representing an opening parenthesis.
Token open_paren() {
    return (Token) { .type=OPEN_PAREN };
}

// return: a token representing a closing parenthesis.
Token close_paren() {
    return (Token) { .type=CLOSE_PAREN };
}

// return: a token representing the end of input.
Token done() {
    return (Token) { .type=DONE };
}

void print_token(Token t) {
    print_token_type(t.type);

    // Print any extra associated data.
    switch (t.type) {
        case INT:
            printf(" '%d'", t.int_val);
            break;
        case BIN_OP:
            printf(" '");
            print_binop(t.bin_op);
            printf("'");
            break;
        default:
            break;
    }
}
