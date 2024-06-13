#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <Logger.hpp>

extern "C" {
    void krnl(void) {
        //asm("mov $0x5, %rax; int $0x80");
    }
}