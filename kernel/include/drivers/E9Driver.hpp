#pragma once
#include <stddef.h>
#include <drivers/driver.hpp>
#include <def.h>

class e9Driver : Driver {
public:
    e9Driver();

    void init();

    void send(char c);
    void send(char* str);
    void send(char* str, size_t n);
};

extern e9Driver E9Driver;