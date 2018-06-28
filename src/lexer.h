#pragma once

#include <stdio.h>
#include <ctype.h>
#include "token.h"

// Keeps track of input consumed so far.
typedef struct {
    char *cs;   // Remaining input.
    Token curr; // Most recently parsed token.
} Tokens;

// effect: advances the pointer to the start of character input stream.
// return: the next character in the character input stream.
char _next_char(Tokens *input) {
    char c = *input->cs;
    input->cs += 1;
    return c;
}

// effect: moves the pointer to the start of the character input stream back one character.
void _back_char(Tokens *input) {
    input->cs -= 1;
}

// effect: moves the input stream onto the next token.
void consume(Tokens *input) {
    char c = _next_char(input);

    if (c == '+') {
        input->curr = bin_op(PLUS);
    }
    else if (c == '-') {
        input->curr = bin_op(SUB);
    }
    else if (isdigit(c)) {
        int n = c - '0';
        c = _next_char(input);
        while (isdigit(c)) {
            n = (n * 10) + (c - '0');
            c = _next_char(input);
        }
        _back_char(input);
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
