#include "drivers/CpuIdDriver.hpp"
#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libc/string.h"
}

CpuIdDriver::CpuIdDriver() { }

void __cpuid(uint32_t type, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    asm volatile("cpuid"
                : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                : "0"(type)); // put the type into eax
}

char* CpuIdDriver::vendor() {
    uint32_t eax, ebx, ecx, edx;
    __cpuid(0, &eax, &ebx, &ecx, &edx);

    char brand[12];

    brand[0] = eax >> 8;
    brand[1] = eax >> 16;
    brand[2] = eax >> 32;
    brand[3] = ebx >> 8;
    brand[4] = ebx >> 16;
    brand[5] = ebx >> 32;
    brand[6] = ecx >> 8;
    brand[7] = ecx >> 16;
    brand[8] = ecx >> 32;
    brand[9] = edx >> 8;
    brand[10] = edx >> 16;
    brand[11] = edx >> 32;

    return brand;

}

extern CpuIdDriver cpuid = CpuIdDriver();