#include <stdint.h>
#include <stddef.h>
#include "includes/idt.h"


// Structure représentant un descripteur d'interruption de l'IDT
struct idt_entry {
  uint16_t base_low;
  uint16_t sel;
  uint8_t always0;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));

// Structure représentant le pointeur de l'IDT
struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

// Tableau de descripteurs d'interruption de l'IDT
struct idt_entry idt[256];

// Pointeur de l'IDT
struct idt_ptr ip;

// Fonction d'initialisation de l'IDT
void idt_init() {
  // Initialiser le pointeur de l'IDT
  ip.limit = sizeof(struct idt_entry) * 256 - 1;
  ip.base = (uint32_t)&idt;

  // Charger l'IDT
  __asm__ volatile("lidt (%0)" : : "p" (&ip));
}

// Fonction de définition d'un descripteur d'interruption de l'IDT
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_low = base & 0xffff;
  idt[num].base_high = (base >> 16) & 0xffff;
  idt[num].sel = sel;
  idt[num].always0 = 0;
  idt[num].flags = flags;
}


