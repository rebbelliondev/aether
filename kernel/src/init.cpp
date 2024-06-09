#include <Logger.hpp>
#include "interrupts/idt.hpp"
#include <drivers/GraphicsDriver.hpp>

extern "C" {
    void init() {
        load_idt();
        //graphics.init();
        Logger.info("Inited kernl");
    }

    void base_revision_unsupported() {
        Logger.error("Limine bootloader base revision unsuported");
    }
}