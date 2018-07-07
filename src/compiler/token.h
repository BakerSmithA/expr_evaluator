#pragma once

// The types of binary operations that can be parsed.
typedef enum {
    PLUS, SUB, MULT, DIV
} BinOp;

void print_binop(BinOp op);

// The types of tokens that can be parsed.
typedef enum {
    INT,         // Has an associated integer value.
    BIN_OP,      // Has an associated operation.
    OPEN_PAREN,  // Has no associated data.
    CLOSE_PAREN, // Has no associated data.
    DONE         // Has no associated data.
} TokenType;

void print_token_type(TokenType type);

// Any of the token types, and associated data.
typedef struct {
    TokenType type;
    union {
        int int_val;
        BinOp bin_op;
    };
} Token;

// return: an integer token containing the given value.
Token integer(int val);

// return: a binary operation token of the given type.
Token bin_op(BinOp op);

// return: a token representing an opening parenthesis.
Token open_paren();

// return: a token representing a closing parenthesis.
Token close_paren();

// return: a token representing the end of input.
Token done();

void print_token(Token t);
