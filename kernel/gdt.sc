#include <stdint.h>
#include <stddef.h>
#include "includes/gdt.h"

// Structure représentant un descripteur de segment de la GDT
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// Structure représentant le pointeur de la GDT
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Tableau de descripteurs de segment de la GDT
struct gdt_entry gdt[3];

// Pointeur de la GDT
struct gdt_ptr gp;

// Fonction d'initialisation de la GDT
void gdt_init() {
    // Initialiser le descripteur de segment null
    gdt[0].limit_low = 0;
    gdt[0].base_low = 0;
    gdt[0].base_middle = 0;
    gdt[0].access = 0;
    gdt[0].granularity = 0;
    gdt[0].base_high = 0;

    // Initialiser le descripteur de segment de code
    gdt[1].limit_low = 0xffff;
    gdt[1].base_low = 0;
    gdt[1].base_middle = 0;
    gdt[1].access = 0x9a;
    gdt[1].granularity = 0xcf;
    gdt[1].base_high = 0;

    // Initialiser le descripteur de segment de données
    gdt[2].limit_low = 0xffff;
    gdt[2].base_low = 0;
    gdt[2].base_middle = 0;
    gdt[2].access = 0x92;
    gdt[2].granularity = 0xcf;
    gdt[2].base_high = 0;

    // Initialiser le pointeur de la GDT
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (uint32_t)&gdt;

    // Charger la GDT
    __asm__ volatile("lgdt (%0)" : : "p" (&gp));
}
