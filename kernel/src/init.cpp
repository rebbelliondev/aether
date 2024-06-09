#include <Logger.hpp>
#include "interrupts/idt.hpp"

extern "C" {
    void init() {
        load_idt();
        Logger.info("Inited kernl");
    }

    void base_revision_unsupported() {
        Logger.error("Limine bootloader base revision unsuported");
    }
}