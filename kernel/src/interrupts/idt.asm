global install_idt

install_idt:
    lidt [rdi]
    sti

    ret