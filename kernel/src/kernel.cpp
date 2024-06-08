extern "C" {
    #include "limine.h"
}

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

extern "C" {
    void krnl(void) {

        // Ensure we got a framebuffer.
        if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) {
            asm ("cli");
            for (;;) {
                asm ("hlt");
            }
        }

        // Fetch the first framebuffer.
        struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

        // Note: we assume the framebuffer model is RGB with 32-bit pixels.
        for (size_t i = 0; i < 100; i++) {
            volatile uint32_t *fb_ptr = (uint32_t*)framebuffer->address;
            fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
        }
    }
}