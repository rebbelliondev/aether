#include <Logger.hpp>
#include <drivers/GraphicsDriver.hpp>
#include "interrupts/IntDriver.hpp"

extern "C" {
    void initSSE();

    #include "mem/paging.h"

    void init() {
        IntDrivr.init();
        IntDrivr.activate(INT_FEATURE::Pic8259);
        IntDrivr.activate(INT_FEATURE::PitTimer);

        enable_paging();
        
        //graphics.init();

        initSSE();

        Logger.info("Inited kernl");
    }

    void base_revision_unsupported() {
        Logger.error("Limine bootloader base revision unsuported");
    }
}