bits 64
global install_idt

install_idt:
    cli
    lidt [rdi]
    sti

    ret