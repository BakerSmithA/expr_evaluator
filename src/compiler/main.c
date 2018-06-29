#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

// effect: creates/opens a file and overwrites the contents with the instructions.
void write_output(char *filename, Bytecode *instrs) {
    FILE *fp = fopen(filename, "wb");
    write_bytecode(instrs, fp);
    fclose(fp);
}

int main(int argc, char *argv[argc]) {
    if (argc != 3) {
        printf("Expected an expression to parse and output filename\n");
        return 0;
    }

    char *input_expr = argv[1];
    char *filename = argv[2];

    Bytecode *output = empty();
    Tokens *ts = from_string(input_expr);
    expr(output, ts);
    write_output(filename, output);

    free_bytecode(output);
    free_tokens(ts);
}
