#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <Logger.hpp>

extern "C" {
    void krnl(void) {
        Logger.info("in the kernel");
    }
}