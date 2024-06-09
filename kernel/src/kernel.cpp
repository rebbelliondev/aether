#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <Logger.hpp>

extern "C" {
    void krnl(void) {
        asm("int $0x5");
        Logger.info("in the kernel");
    }
}