#pragma once

#include <stdint.h>
#include <stddef.h>

#define MASTER_PIC_CMD  0x20
#define MASTER_PIC_DATA 0x21
#define SLAVE_PIC_CMD   0xA0
#define SLAVE_PIC_DATA  0xA1

#define PIC_EOI 0x20

class Pic8259 {
public:

    Pic8259();

    void eoi(uint8_t irq);
    void remap(int offset1, int offset2);
    void activate(uint8_t IRQline);
    void disable();
};

extern Pic8259 pic;