global load_gdt
global reloadSegments

load_gdt:
    mov rax, rdi
    lgdt [rax] ; error here

    cli
    ret

reloadSegments:
    push 0x08
    lea rax, [rel .reloadCS]
    retf

.reloadCS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret