#pragma once

#include <stdio.h>
#include <stdbool.h>

// Used to determine nesting of tests.
typedef int Ctx;

// effect: prints a number of tabs to correctly indent a Ctx or test name.
void print_indentation(Ctx ctx) {
    for (int i=0; i<ctx; i++) {
        printf("\t");
    }
}

// effect: prints the name of the context followed by a semicolon.
void print_ctx_name(char *name) {
    printf("%s:\n", name);
}

// effect: prints the name of the context and returns a 0 indentation level.
Ctx new_ctx(char *name) {
    print_ctx_name(name);
    return 0;
}

// effect: prints the name of the context and returns the new indentation level.
Ctx nested_ctx(char *name, Ctx ctx) {
    Ctx new_ctx = ctx + 1;
    print_indentation(new_ctx);
    print_ctx_name(name);
    return new_ctx;
}

// effect: returns an identiation level for printing test results.
Ctx testing_ctx(Ctx ctx) {
    return ctx + 1;
}

// effect: prints whether the test succeeded or failed, i.e. whether result is
//         true or false.
void test(bool result, char *name, Ctx ctx) {
    print_indentation(testing_ctx(ctx));
    if (result) {
        printf("pass: %s\n", name);
    } else {
        printf("fail: %s\n", name);
    }
}
