#include "test_bytecode.h"
#include "test_lexer.h"

int main(void) {
    Ctx compiler_ctx = new_ctx("compiler");
    test_bytecode(compiler_ctx);
    test_lexer(compiler_ctx);
}
