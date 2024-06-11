bits 64
global intHandler
extern interrupt_isr

intHandler:
    pushaq

    call interrupt_isr

    popaq
    iretq