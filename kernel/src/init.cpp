#include <Logger.hpp>
#include "interrupts/idt.hpp"
// #include "PitTimerDriver.hpp"
#include <drivers/GraphicsDriver.hpp>

extern "C" {
    #include "interrupts/gdt.h"

    void init() {
        load_gdt();
        load_idt();
       //  pitTimer.init();
        
        //graphics.init();

        Logger.info("Inited kernl");
    }

    void base_revision_unsupported() {
        Logger.error("Limine bootloader base revision unsuported");
    }
}