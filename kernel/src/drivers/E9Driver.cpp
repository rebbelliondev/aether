#include <drivers/E9Driver.hpp>
#include <drivers/IoDriver.hpp>

#ifdef DEBUG
#include <Logger.hpp>
#endif

e9Driver::e9Driver() { }

void e9Driver::init() {
#ifdef DEBUG
    Logger.sucess("inited e9");
#endif
}

void e9Driver::send(char c) {
    IoDriver.outb(0xe9, c);
}

void e9Driver::send(char* str) {
    size_t i = 0;
    while (str[i] != '\0') {
        this->send(str[i]);
        i++;
    }
}

void e9Driver::send(char* str, size_t n) {
    size_t i = 0;
    while (i < n) {
        this->send(str[i]);
        i++;
    }

}

extern e9Driver E9Driver = e9Driver();