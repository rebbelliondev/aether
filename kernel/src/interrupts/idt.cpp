#include "libc/string.h"
#include "idt.hpp"
#include "pic8259.hpp"

extern "C" {
    #include "gdt.h"
}

__attribute__((aligned(0x10)))
struct idtentry idt[256];

static idt_ptr idtp = {
    .limit = sizeof(idt) - 1,
    .base = (uint64_t)&idt,
};

void set_idt_entry(int n, uint64_t handler) {
    idt[n].offset_1 =(uint64_t) handler & 0xFFFF;
    idt[n].selector = 0x8;
    idt[n].ist = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_2 = ((uint64_t)handler >> 16) & 0xFFFF;
    idt[n].offset_3 = ((uint64_t)handler >> 32) & 0xFFFFFFFF;
    idt[n].zero = 0;
}

extern const uint64_t isr_table[256];

void registerHandler(int n, uint64_t adr) {
    //g_ints[n] = adr;
}

extern "C" void intHandler();

extern "C" void install_idt(uint64_t);

void load_idt(void) {
    for (int i = 0; i < 256; i++) {
        set_idt_entry(i, isr_table[i]);
    }
 
    pic.remap(32, 32 + 7);

    install_idt((uint64_t)&idtp);
}


