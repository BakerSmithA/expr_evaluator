#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Keeps track of input consumed so far.
struct Tokens {
    char *cs;   // Remaining input.
    Token curr; // Most recently parsed token.
};

void print_tokens(Tokens *tokens) {
    printf("Tokens<%s>", tokens->cs);
}

// effect: advances the pointer to the start of character input stream.
// return: the next character in the character input stream.
static char next_char(Tokens *input) {
    char c = *input->cs;
    input->cs += 1;
    return c;
}

// effect: moves the pointer to the start of the character input stream back one character.
static void back_char(Tokens *input) {
    input->cs -= 1;
}

// effect: moves the input stream onto the next token.
void consume(Tokens *input) {
    input->curr = whitespace();

    while (input->curr.type == WHITESPACE) {
        char c = next_char(input);

        if (c == ' ' || c == '\t') {
            input->curr = whitespace();
        }
        else if (c == '+') {
            input->curr = bin_op(PLUS);
        }
        else if (c == '-') {
            input->curr = bin_op(SUB);
        }
        else if (c == '*') {
            input->curr = bin_op(MULT);
        }
        else if (c == '/') {
            input->curr = bin_op(DIV);
        }
        else if (c == '(') {
            input->curr = open_paren();
        }
        else if (c == ')') {
            input->curr = close_paren();
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
}

// return: the token at the start of the input stream.
Token lookahead(Tokens *input) {
    return input->curr;
}

// return: the input initialised with the given input string.
Tokens *from_string(char *input) {
    Tokens *ts = (Tokens*)malloc(sizeof(Tokens));
    ts->cs = input;
    consume(ts);
    return ts;
}

// effect: frees the tokens. However, does not free the remaining input string
//         that was passed to from_string when creating the Tokens.
void free_tokens(Tokens *tokens) {
    free(tokens);
}
