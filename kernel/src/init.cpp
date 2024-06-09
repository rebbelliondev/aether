#include <Logger.hpp>
#include "interrupts/idt.hpp"
#include <drivers/CpuIdDriver.hpp>

extern "C" {
    void init() {
        load_idt();
        //Logger.info(cpuid.vendor());
        Logger.info("Inited kernl");
    }
}