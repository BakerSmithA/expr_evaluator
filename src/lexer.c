#include <ctype.h>

// typedef char Token;
// typedef Token* Tokens;

// The types of tokens that can be parsed.
typedef enum {
    INT, BIN_OP
} TokenType;

// The types of binary operations that can be parsed.
typedef enum {
    PLUS, MINUS
} BinOp;

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
    return (Token) { INT, val };
}

// return: a binary operation token of the given type.
Token bin_op(BinOp op) {
    return (Token) { BIN_OP, op };
}
