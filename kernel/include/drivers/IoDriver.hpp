#pragma once
#include <stdint.h>
#include <stddef.h>
#include <def.h>
#include <drivers/driver.hpp>

class ioDriver : Driver {
public:
    ioDriver();

    void outb(uint16_t port, uint8_t data);
    uint8_t inb(uint16_t port);

    void outw(uint16_t port, uint16_t data);
    uint16_t inw(uint16_t port);
    
};

extern ioDriver IoDriver;