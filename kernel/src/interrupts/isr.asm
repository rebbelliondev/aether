bits 64
global intHandler

extern interrupt_isr

intHandler:
	cli
	push rsp
	push rbx
	push rax

	mov rdi, rsp
    call interrupt_isr 

	pop rsp
	pop rbx
	pop rax
	sti
    iretq