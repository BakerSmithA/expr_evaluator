#include "test_bytecode.h"

int main(void) {
    Ctx compiler_ctx = new_ctx("compiler");
    test_bytecode(compiler_ctx);
}
