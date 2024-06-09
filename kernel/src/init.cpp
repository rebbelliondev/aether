#include <Logger.hpp>
#include "interrupts/idt.hpp"

extern "C" {
    void init() {
        load_idt();

        Logger.info("Inited kernl");
    }
}