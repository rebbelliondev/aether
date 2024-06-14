#pragma once

#include <stdint.h>

 struct idtentry {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t zero;
}__attribute__((packed));

typedef struct REGISTERS {
    uint64_t int_no, 
            rax, rbx, rcx, rdx, rsi, rdi, 
            r8, r9, r10, r11, r12, r13, r14, r15;
} __attribute__((packed));

typedef void *(ISR)(REGISTERS*);

struct idt_ptr {
    uint16_t limit;
    uint64_t base;
}__attribute__((packed));