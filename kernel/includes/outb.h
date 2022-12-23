#ifndef __OUTB__H__
#define __OUTB__H__
// Fonction d'écriture d'un octet sur un port I/O
void outb(uint16_t port, uint8_t val);
unsigned int inb(unsigned int port);
#endif
