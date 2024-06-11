bits 64
global install_idt

install_idt:
    sti
    lidt [rdi]
    

    ret