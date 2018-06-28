#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

// typedef char* Tokens;
//
// // Returns the next token on the input stream.
// char lookahead(Tokens *ts) {
//     return **ts;
// }
//
// // Consumes the next token on the input stream of tokens.
// void consume(Tokens *ts) {
//     *ts += 1;
// }
//
// // Matches on terms, i.e. digits 0-9.
// void term(Tokens *ts) {
//     char t = lookahead(ts);
//     if (isdigit(t)) {
//         printf("%c", t);
//         consume(ts);
//     } else {
//         printf("\nExpected digit but got %c\n", t);
//         exit(0);
//     }
// }
//
// // Matches on expressions, i.e. digits separated by operators. E.g. 0+1, 9+5+1
// void expr(Tokens *ts) {
//     term(ts);
//     while (1) {
//         char t = lookahead(ts);
//
//         if (t == '+') {
//             consume(ts); term(ts); printf("+");
//         }
//         else if (t == '-') {
//             consume(ts); term(ts); printf("-");
//         }
//         else {
//             break;
//         }
//     }
// }
//
// int main(int argc, char *argv[argc]) {
//     if (argc != 2) {
//         printf("Expected an expression to parse\n");
//         return 0;
//     }
//
//     Tokens *ts = &argv[1];
//
//     printf("%s\n", *ts);
//     expr(ts);
//     printf("\n");
// }

void term(Tokens *input) {
    Token t = lookahead(input);
    switch (t.type) {
        case INT:
            printf("%d", t.int_val);
            break;
        default:
            printf("Expected integer, but got ");
            print_token(t);
            printf("\n");
            break;
    }
}

int main(int argc, char *argv[argc]) {
    if (argc != 2) {
        printf("Expected an expression to parse\n");
        return 0;
    }

    Tokens ts = from_string(argv[1]);
    term(&ts);
    printf("\n");
}
