#pragma once

#include <stdio.h>
#include <ctype.h>

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

// Keeps track of input consumed so far.
typedef struct {
    char *cs;   // Remaining input.
    Token curr; // Most recently parsed token.
} Tokens;

// effect: advances the pointer to the start of character input stream.
// return: the next character in the character input stream.
char next_char(Tokens *input) {
    char c = *input->cs;
    input->cs += 1;
    return c;
}

// effect: moves the pointer to the start of the character input stream back one character.
void back_char(Tokens *input) {
    input->cs -= 1;
}

// effect: moves the input stream onto the next token.
void consume(Tokens *input) {
    char c = next_char(input);

    if (c == '+') {
        input->curr = bin_op(PLUS);
    }
    else if (c == '-') {
        input->curr = bin_op(SUB);
    }
    else if (isdigit(c)) {
        int n = c - '0';
        c = next_char(input);
        while (isdigit(c)) {
            n = (n * 10) + (c - '0');
            c = next_char(input);
        }
        back_char(input);
        input->curr = integer(n);
    }
    else if (c == '\0') {
        input->curr = done();
    }
}

// return: the token at the start of the input stream.
Token lookahead(Tokens *input) {
    return input->curr;
}

// return: the input initialised with the given input string.
Tokens from_string(char *cs) {
    Tokens ts;
    ts.cs = cs;
    consume(&ts);
    return ts;
}
