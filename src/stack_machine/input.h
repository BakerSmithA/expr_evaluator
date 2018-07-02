#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_codes;
    char *codes;
} Bytecode;

// return: a new bytecode object allocated on the heap.
Bytecode *_new_bytecode(int num_codes, char *codes) {
    Bytecode *b = (Bytecode*)malloc(sizeof(Bytecode));
    *b = (Bytecode) { .num_codes=num_codes, .codes=codes };
    return b;
}

// effect: frees the codes contained in the bytecode, as well as the pointer to
//         the bytecode object.
void free_bytecode(Bytecode *b) {
    free(b->codes);
    free(b);
}

// effect: sets the file position indicator to the start of the file.
// return: the size of the file in bytes.
int _file_size(FILE *fp) {
    fseek(fp, 0L, SEEK_SET);
    fseek(fp, 0L, SEEK_END);
    int num_bytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return num_bytes;
}

// return: the entire contents of a file, or NULL if unsuccessful.
Bytecode *read_file(char *filename) {
    FILE *fp = fopen(filename, "rb");

    if(fp == NULL) {
        printf("File does not exist\n");
        return NULL;
    }

    int num_bytes = _file_size(fp);
    char *contents = (char*)malloc(num_bytes);

    fread(contents, sizeof(char), num_bytes, fp);
    fclose(fp);

    return _new_bytecode(num_bytes, contents);
}
