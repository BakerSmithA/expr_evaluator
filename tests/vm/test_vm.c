#include "test_stack.h"

int main(void) {
    Ctx vm_ctx = new_ctx("virtual machine");
    test_stack(vm_ctx);
}
