#include "test_stack.h"
#include "test_interpreter.h"

int main(void) {
    Ctx vm_ctx = new_ctx("virtual machine");
    test_stack(vm_ctx);
    test_interpreter(vm_ctx);
}
