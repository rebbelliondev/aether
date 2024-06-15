#include "IntDriver.hpp"
#include "idt/idt.hpp"

#include "pic/Pic8259.hpp"
#include "pic/PitTimerDriver.hpp"

extern "C" {
    #include "gdt/gdt.h"
}

IntDriver::IntDriver() {}

extern "C" uint64_t g_ints[256];
extern const uint64_t isr_table[256];
extern "C" void install_idt(uint64_t);


__attribute__((aligned(0x10)))
struct idtentry idt[256];

static idt_ptr idtp = {
    .limit = sizeof(idt) - 1,
    .base = (uint64_t)&idt,
};

void IntDriver::init() {

    load_gdt();

    for (int i = 0; i < 256; i++) {
        idt[i].offset_1 =(uint64_t) isr_table[i] & 0xFFFF;
        idt[i].selector = 0x8;
        idt[i].ist = 0;
        idt[i].type_attr = 0x8E;
        idt[i].offset_2 = ((uint64_t)isr_table[i] >> 16) & 0xFFFF;
        idt[i].offset_3 = ((uint64_t)isr_table[i] >> 32) & 0xFFFFFFFF;
        idt[i].zero = 0;
    }
 

    install_idt((uint64_t)&idtp);
}

void IntDriver::activate(INT_FEATURE feature) {
    switch ( feature ) {
        case INT_FEATURE::Pic8259: {
            if (!this->pic8259_inited) {
                pic.remap(32, 32 + 7);
            }
        }

        case INT_FEATURE::PitTimer: {
            if (!this->pit_timer_inited) {
                this->activate(INT_FEATURE::Pic8259);

                pit.init();
            }
        }
    }
}

void IntDriver::setHandler(int n, uint64_t handler) {
    if (n < 256) {
        g_ints[n] = handler;
    }
}

extern IntDriver IntDrivr = IntDriver();