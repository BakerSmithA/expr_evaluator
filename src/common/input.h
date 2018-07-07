#pragma once

#include <stdio.h>

// effect: sets the file position indicator to the start of the file.
// return: the size of the file in bytes.
int file_size(FILE *fp);

// return: the entire contents of a file, or NULL if unsuccessful.
char *read_file(char *filename);
