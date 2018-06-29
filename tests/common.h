#pragma once

#include <stdio.h>
#include <stdbool.h>

void context(char *name) {
    printf("%s:\n", name);
}

// effect: prints whether the test succeeded or failed, i.e. whether result is
//         true or false.
void test(bool result, char *name) {
    if (result) {
        printf("\tpass: %s\n", name);
    } else {
        printf("\tfail: %s\n", name);
    }
}
