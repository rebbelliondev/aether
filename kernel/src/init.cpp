#include <Logger.hpp>

extern "C" { 
    #include "interrupts/idt.h"
}

extern "C" {
    void init() {
        load_idt();

        Logger.info("Inited kernl");
    }
}