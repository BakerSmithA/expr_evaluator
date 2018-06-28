#pragma once

// The types of binary operations that can be parsed.
typedef enum {
    PLUS, SUB
} BinOp;

void print_binop(BinOp op) {
    switch (op) {
        case PLUS:
            printf("+");
            break;
        case SUB:
            printf("-");
            break;
    }
}

// The types of tokens that can be parsed.
typedef enum {
    INT,    // Has an associated integer value.
    BIN_OP, // Has an associated operation.
    DONE    // Has no associated data.
} TokenType;

// Either a integer or binary operator.
typedef struct {
    TokenType type;
    union {
        int int_val;
        BinOp bin_op;
    };
} Token;

// return: an integer token containing the given value.
Token integer(int val) {
    return (Token) { .type=INT, { .int_val=val } };
}

// return: a binary operation token of the given type.
Token bin_op(BinOp op) {
    return (Token) { .type=BIN_OP, { .bin_op=op } };
}

// return: a token representing the end of input.
Token done() {
    return (Token) { .type=DONE };
}

void print_token(Token t) {
    switch (t.type) {
        case INT:
            printf("Integer(%d)", t.int_val);
            break;
        case BIN_OP:
            printf("BinOp(");
            print_binop(t.bin_op);
            printf(")");
            break;
        case DONE:
            printf("End");
            break;
    }
}
