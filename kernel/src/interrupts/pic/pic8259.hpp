#pragma once

#include <stdint.h>
#include <stddef.h>

#define MASTER_PIC_CMD  0x20
#define MASTER_PIC_DATA 0x21
#define SLAVE_PIC_CMD   0xA0
#define SLAVE_PIC_DATA  0xA1

#define PIC_EOI 0x20

class pic8259 {
public:
    pic8259();

    void eoi(uint8_t irq);
    void remap(int offset1, int offset2);
    void activate(uint8_t IRQline);
    void disable();
};

extern pic8259 pic;