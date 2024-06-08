#include "../libc/string.c"
#include "idt.h"

struct idtentry idt[256];
struct idt_ptr idtp;

void set_idt_entry(int n, uint32_t handler) {
    idt[n].offset_1 = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].ist = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_2 = (handler >> 16) & 0xFFFF;
    idt[n].offset_3 = (handler >> 32) & 0xFFFFFFFF;
    idt[n].zero = 0;
}

void load_idt(void) {
    idtp.limit = (sizeof(struct idtentry) * 256) - 1;
    idtp.base = (uint64_t)&idt;
    memset(&idt, 0, sizeof(struct idtentry) * 256);
    // Need to add isr common handler to put entries through
    
    __asm__ __volatile__("lidt(%0)" : : "r" (&idtp));
}