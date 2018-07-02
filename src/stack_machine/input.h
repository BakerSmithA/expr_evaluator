#pragma once

#include <stdio.h>
#include <stdlib.h>

// effect: sets the file position indicator to the start of the file.
// return: the size of the file in bytes.
int file_size(FILE *fp) {
    fseek(fp, 0L, SEEK_SET);
    fseek(fp, 0L, SEEK_END);
    int num_bytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return num_bytes;
}

// return: the entire contents of a file, or NULL if unsuccessful.
char *read_file(char *filename) {
    FILE *fp = fopen(filename, "rb");

    if(fp == NULL) {
        return NULL;
    }

    int num_bytes = file_size(fp);
    char *contents = (char*)malloc(num_bytes);

    fread(contents, sizeof(char), num_bytes, fp);
    fclose(fp);

    return contents;
}
