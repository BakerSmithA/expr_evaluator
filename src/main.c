#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

void err_expected(char *expected, Token actual) {
    printf("Expected %s but got ", expected);
    print_token(actual);
    printf("\n");
    exit(0);
}

void term(Tokens *input) {
    Token t = lookahead(input);
    switch (t.type) {
        case INT:
            printf("%d ", t.int_val);
            consume(input);
            break;
        default:
            err_expected("integer", t);
            break;
    }
}

void expr(Tokens *input) {
    term(input);
    while (1) {
        Token t = lookahead(input);

        if (t.type == BIN_OP) {
            consume(input);
            term(input);
            print_binop(t.bin_op);
            printf(" ");
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

int main(int argc, char *argv[argc]) {
    if (argc != 2) {
        printf("Expected an expression to parse\n");
        return 0;
    }

    Tokens ts = from_string(argv[1]);
    expr(&ts);
    printf("\n");
}
