#include "test_bytecode.h"
#include "test_lexer.h"
#include "test_parser.h"

int main(void) {
    Ctx compiler_ctx = new_ctx("compiler");
    test_bytecode(compiler_ctx);
    test_lexer(compiler_ctx);
    test_parser(compiler_ctx);
}
