#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char *argv[argc]) {
    if (argc != 2) {
        printf("Expected an expression to parse\n");
        return 0;
    }

    Bytecode *output = empty();
    Tokens ts = from_string(argv[1]);
    expr(output, &ts);
    print_bytecode(output);
    printf("\n");
}
