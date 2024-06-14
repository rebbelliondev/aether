#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "limine.h"

__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);

// Halt and catch fire function.
static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

extern void krnl();
extern void base_revision_unsupported();
extern void init();

void _start(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        base_revision_unsupported();
        hcf();
    }

    init();
    krnl();
  // PAGING IS READY, I used a teeny bit of chatgpt to speed it up (sorry!!!) I promise I won't use chatgpt from now on (we need implementation of the virtual memory)


    hcf();
}