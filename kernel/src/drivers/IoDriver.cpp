#include <drivers/IoDriver.hpp>

ioDriver::ioDriver() {}

void ioDriver::outb(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint8_t ioDriver::inb(uint16_t port) {
    uint8_t result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void ioDriver::outw(uint16_t port, uint16_t data) {
    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}

uint16_t ioDriver::inw(uint16_t port) {
    uint16_t result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;

}

extern ioDriver IoDriver = ioDriver();