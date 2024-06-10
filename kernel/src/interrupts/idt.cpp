#include "libc/string.h"
#include "idt.hpp"
#include "pic8259.hpp"

struct idtentry idt[256];
struct idt_ptr idtp;

void set_idt_entry(int n, uint64_t handler) {
    idt[n].offset_1 = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].ist = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_2 = (handler >> 16) & 0xFFFF;
    idt[n].offset_3 = (handler >> 32) & 0xFFFFFFFF;
    idt[n].zero = 0;
}

extern "C" uint64_t g_ints[256];

void registerHandler(int n, uint64_t adr) {
    g_ints[n] = adr;
}

extern "C" void intHandler();

extern "C" void install_idt(uint64_t);

void load_idt(void) {
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint64_t)&idt;


    for (int i = 0; i < 32; i++) {
        set_idt_entry(i, (uint64_t)intHandler);
    }
 
    pic.remap(32, 32 + 7);

    //install_idt((uint64_t)&idt);
}