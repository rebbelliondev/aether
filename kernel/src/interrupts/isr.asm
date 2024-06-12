bits 64

section .text
extern interrupt_isr

%assign i 0
%rep 256
int_%+ i:
	cli

	push rsp

	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push r8
	push rdi
	push rsi
	push rdx
	push rcx
	push rbx
	push rax

	mov rax, i
	push rax

	mov rdi, rsp
    call interrupt_isr 

	pop rax


	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r8
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax

	pop rsp

	sti
	
    iret

%assign i i + 1
%endrep

section .rodata
global isr_table
isr_table:
	%assign i 0
	%rep 256
	dq int_%+ i
	%assign i i + 1
	%endrep