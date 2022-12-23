#include <stdint.h>
#include <stddef.h>
#include "includes/outb.h"

// Fonction d'écriture d'un octet sur un port I/O
void outb(uint16_t port, uint8_t val) {
  // Utiliser un pointeur volatil pour accéder au port en mémoire
  *((volatile uint8_t*)port) = val;
}

// Fonction de lecture d'un octet sur un port I/O
unsigned int inb(unsigned int port){
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
    return (unsigned int) value;
}
