#include <Logger.hpp>
#include "interrupts/idt.hpp"
#include "interrupts/PitTimerDriver.hpp"
#include <drivers/GraphicsDriver.hpp>

extern "C" {
    void initSSE();

    #include "interrupts/gdt.h"

    void init() {
        load_gdt();
        load_idt();
        pit.init();
        
        //graphics.init();

        initSSE();

        Logger.info("Inited kernl");
    }

    void base_revision_unsupported() {
        Logger.error("Limine bootloader base revision unsuported");
    }
}