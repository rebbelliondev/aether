#include "pic8259.hpp"
#include <drivers/IoDriver.hpp>

void Pic8259::eoi(uint8_t irq) {
    if (irq >= 8) {
        IoDriver.outb(SLAVE_PIC_CMD, PIC_EOI);
    }

    IoDriver.outb(MASTER_PIC_CMD, PIC_EOI);
};

inline void io_wait() {
    for (int i = 0; i < 100000 ; i++) {
        asm volatile("nop");
    }
}


Pic8259::Pic8259() { }

void Pic8259::remap(int offset1, int offset2) {
    uint8_t a1 = IoDriver.inb(MASTER_PIC_DATA);
    uint8_t a2 = IoDriver.inb(SLAVE_PIC_DATA);

    IoDriver.outb(MASTER_PIC_CMD, 0x11);
    io_wait();
    IoDriver.outb(SLAVE_PIC_CMD, 0x11);
    io_wait();

    IoDriver.outb(MASTER_PIC_DATA,  offset1);
    io_wait();
    IoDriver.outb(SLAVE_PIC_DATA,  offset2);
    io_wait();

    IoDriver.outb(MASTER_PIC_DATA, 4);
    io_wait();
    IoDriver.outb(SLAVE_PIC_DATA, 2);
    io_wait();

    IoDriver.outb(MASTER_PIC_DATA, 0x01);
    io_wait();
    IoDriver.outb(SLAVE_PIC_DATA, 0x01);
    io_wait();

    IoDriver.outb(MASTER_PIC_DATA, a1);
    IoDriver.outb(SLAVE_PIC_DATA, a2);
}

void Pic8259::disable() {
    IoDriver.outb(MASTER_PIC_DATA, 0xff);
    IoDriver.outb(SLAVE_PIC_DATA, 0xff);
}

void Pic8259::activate(uint8_t IRQline) {

    uint16_t port;
    uint8_t value;

    if (IRQline < 8) {
        port = MASTER_PIC_DATA;
    } else {
        port = SLAVE_PIC_DATA;
        IRQline -= 8;
    }

    value = IoDriver.inb(port) | ( 1 << IRQline );
    IoDriver.outb(port, value);
}

extern Pic8259 pic = Pic8259();