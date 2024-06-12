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

const char* exceptions[32] = {
    "Division Error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocssor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved",
};


typedef struct REGISTERS{
    uint64_t rax, rbx;
} __attribute__((packed));


#include "LogFmt.hpp"


extern "C" {
    extern REGISTERS regs;

    void interrupt_isr(REGISTERS* regs) {
        printf("REGISTERS:\n");
        printf("rax=0x%x; rbx=0x%x\n", regs->rax, regs->rbx);

        if (regs->rax == 5) {
            printf("right value");
            printf("%d", regs->rax);
        } else {
            printf("wrong value");
        }

        asm volatile("cli; hlt");
    }
}