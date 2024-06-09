#include <Logger.hpp>
#include <stdint.h>

struct interrupt_frame
{
    uint16_t ip;
    uint16_t cs;
    uint16_t flags;
    uint16_t sp;
    uint16_t ss;
};

extern "C" {
    void intHandler(struct interrupt_frame* frame) {
        Logger.info("Interrupt");
    }
}