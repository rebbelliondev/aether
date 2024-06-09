/*#include <drivers/GraphicsDriver.hpp>
#include <stddef.h>

#include <Logger.hpp>

#include "string.h"
#define SSFN_CONSOLEBITMAP_TRUECOLOR
#define SSFN_IMPLEMENTATION
#include "ssfn.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

GraphicsDriver::GraphicsDriver() {}

void GraphicsDriver::putPixel(int x, int y, long color) {
    uint32_t *fb_ptr = reinterpret_cast<uint32_t*>(this->framebuf.address);
    fb_ptr[y * (this->getPitch() / 4) + x] = color;
}

void GraphicsDriver::init() {
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        Logger.error("could not get framebuffer response");
    } else {
        // Fetch the first framebuffer.
        struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

        this->framebuf = *framebuffer;
        Logger.sucess("inited graphics driver");

        ssfn_src = &_binary_console_sfn_start;
        ssfn_dst.ptr = (uint8_t*)this->framebuf.address;
        ssfn_dst.p = 4096;
        ssfn_dst.fg = 0xFFFFFFFF;
        ssfn_dst.bg = 0;
        ssfn_dst.x = 10;
        ssfn_dst.y = 10;
        ssfn_dst.w = this->framebuf.width;
        ssfn_dst.h = this->framebuf.height;
    }
}

void GraphicsDriver::print(char* msg) {
    for (int i = 0; msg[i] != 0; i++) {
        ssfn_putc(msg[i]);
    }
}

uint64_t GraphicsDriver::getPitch() {
    return this->framebuf.pitch;
}

uint64_t GraphicsDriver::getHeight() {
    return this->framebuf.height;
}

uint64_t GraphicsDriver::getWidth() {
    return this->framebuf.width;
}

uint16_t GraphicsDriver::getBpp() {
    return this->framebuf.bpp;
}

uint8_t GraphicsDriver::getMemory_model() {
    return this->framebuf.memory_model;
}

uint8_t GraphicsDriver::getRed_mask_size() {
    return this->framebuf.red_mask_size;
}

uint8_t GraphicsDriver::getRed_mask_shift() {
    return this->framebuf.red_mask_shift;
}

uint8_t GraphicsDriver::getGreen_mask_size() {
    return this->framebuf.green_mask_size;
}

uint8_t GraphicsDriver::getGreen_mask_shift() {
    return this->framebuf.green_mask_shift;
}

uint8_t GraphicsDriver::getBlue_mask_size() {
    return this->framebuf.blue_mask_size;
}

uint8_t GraphicsDriver::getBlue_mask_shift() {
    return this->framebuf.blue_mask_shift;
}

extern GraphicsDriver graphics = GraphicsDriver();*/