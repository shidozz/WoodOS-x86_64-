#ifndef __IDT__H__
#define __IDT__H__

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_init();

#endif