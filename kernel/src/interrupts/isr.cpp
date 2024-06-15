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

#include "LogFmt.hpp"

#include "idt/idt.hpp"

extern "C" {
    ISR* g_ints[256];

    void interrupt_isr(REGISTERS* regs) {

        if ( regs->int_no < 32 ) {
            printf("exception: %s\n", exceptions[regs->int_no]);
        }

        printf("REGISTERS:\n");
        printf("int 0x%X\n", regs->int_no);
        printf("rax=0x%x; rbx=0x%x; rcx=0x%x; rdx=0x%x; rsi=0x%x; rdi=0x%x\n", regs->rax, regs->rbx, regs->rcx, regs->rdx, regs->rsi, regs->rdi);
        printf("r8=%x; r9=%x; r10=%x; r11=%x; r12=%x; r13=%x; r14=%x; r15=%x\n", regs->r8, regs->r9, regs->r10, regs->r11, regs->r12, regs->r13, regs->r14, regs->r15);

        if (regs->int_no > 31 && g_ints[regs->int_no] != nullptr) {
            g_ints[regs->int_no](regs);
        }

        if ( regs->int_no < 32 ) {
            asm volatile("cli; hlt");
        }
    }
}