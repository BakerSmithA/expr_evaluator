#pragma once

#include "token.h"

// Keeps track of input consumed so far.
typedef struct Tokens Tokens;

void print_tokens(Tokens *tokens);

// effect: moves the input stream onto the next token.
void consume(Tokens *input);

// return: the token at the start of the input stream.
Token lookahead(Tokens *input);

// return: the input initialised with the given input string.
Tokens *from_string(char *input);

// effect: frees the tokens. However, does not free the remaining input string
//         that was passed to from_string when creating the Tokens.
void free_tokens(Tokens *tokens);
