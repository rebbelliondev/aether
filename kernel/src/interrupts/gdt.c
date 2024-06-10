

#include <stdio.h>
#include <stdint.h>
#include "gdt.h"

uint64_t gdt[5];

uint64_t descriptor(uint32_t base, uint32_t limit, uint16_t flag) {
    uint64_t descriptor;

    descriptor = limit & 0x000F0000;
    descriptor |= (flag << 8) & 0x00F0FF00;
    descriptor |= (base >> 16) & 0x000000FF;
    descriptor |= base & 0xFF000000;

    descriptor <<= 32;
    descriptor |= base << 16;
    descriptor |= limit & 0x0000FFFF;

    return descriptor;
}

typedef struct {
	uint16_t size;
	uint64_t addr;
} __attribute__((packed)) gdtr_t;

extern void install_gdt(uint64_t);
extern void reloadSegments();

void load_gdt(void) {

    gdt[0] = descriptor(0, 0, 0);
    gdt[1] = descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt[2] = descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt[3] = descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt[4] = descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

    gdtr_t gdtr = {
        .size = sizeof(gdt) - 1,
        .addr = (uint64_t)&gdt,
    };

    install_gdt((uint64_t)&gdtr);
}