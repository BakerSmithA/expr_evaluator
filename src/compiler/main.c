#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "../common/input.h"

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

    char *input_file = argv[1];
    char *output_file = argv[2];

    char *input_tokens = read_file(input_file);

    Bytecode *output = empty();
    Tokens *ts = from_string(input_tokens);

    parse(output, ts);
    write_output(output_file, output);

    free_bytecode(output);
    free_tokens(ts);

    printf("Done\n");
}
