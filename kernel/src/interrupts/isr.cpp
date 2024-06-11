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

typedef struct {
    uint32_t ds;
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;
    uint32_t int_no, err_code;                        // interrupt number and error code
    uint32_t eip, cs, eflags, useresp, ss;            // pushed by the processor automatically
} REGISTERS;

extern "C" {

    void interrupt_isr(REGISTERS regs) {
        debugf("REGISTERS:\n");
        debugf("int=%x\n", regs.int_no);
        debugf("err_code=%d\n", regs.err_code);
        debugf("eax=0x%x, ebx=0x%x, ecx=0x%x, edx=0x%x\n", regs.rax, regs.rbx, regs.rcx, regs.rdx);
        debugf("edi=0x%x, esi=0x%x, ebp=0x%x, esp=0x%x\n", regs.rdi, regs.rsi, regs.rbp, regs.rsp);
        debugf("eip=0x%x, cs=0x%x, ss=0x%x, eflags=0x%x, useresp=0x%x\n", regs.eip, regs.ss, regs.eflags, regs.useresp);
        Logger.error("exception");

        asm volatile("cli; hlt");
    }
}