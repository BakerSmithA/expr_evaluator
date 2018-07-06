#include <stdio.h>
#include "../common/input.h"
#include "interpreter.h"

int main(int argc, char *argv[argc]) {
    if (argc != 2) {
        printf("Expected file to run\n");
        return 0;
    }

    char *filename = argv[1];
    char *bytecode = read_file(filename);

    if (bytecode == NULL) {
        printf("Could not open file\n");
        return 0;
    }

    Interpreter *inter = new_interpreter(bytecode);
    int result = interpret(inter);
    free_interpreter(inter);

    printf("Result: %d\n", result);
}
