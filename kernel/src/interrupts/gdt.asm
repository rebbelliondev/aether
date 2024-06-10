global load_gdt
global reloadSegments

gdtr DW 0 ; For limit storage
     DQ 0 ; For base storage
 
load_gdt:
   cli
   
   mov   [gdtr], di
   mov   [gdtr+2], rsi
   lgdt  [gdtr]

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