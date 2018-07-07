#include "lexer.h"
#include "bytecode.h"
#include "../common/codes.h"

// effect: parses the input and produces bytecode to calculate the result.
void parse(Bytecode *instrs, Tokens *input);
