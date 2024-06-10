global load_gdt

load_gdt:
    lgdt [rdi]
    call reloadSegments
    ret

reloadSegments:
    push 0x08
    lea rax, [rel .reloadCS]
    retfq

.reloadCS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret