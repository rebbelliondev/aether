
section text
    global isr
    extern intHandler

isr:
    pushaq
    cld   
    call  intHandler
    popaq
    iret

