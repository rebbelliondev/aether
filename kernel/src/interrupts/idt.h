#include <stdint.h>
#ifndef _IDT_H

 struct idtentry{
    uint16_t offset_1;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t zero;
}__attribute__((packed));


struct idt_ptr {
uint16_t limit;
uint32_t base;
}__attribute__((packed));

void set_idt_entry(int n, uint32_t handler);
void load_idt(void);

#endif
