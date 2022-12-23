#include <stddef.h>
#include <stdint.h>
#include "includes/terminal.h"
#include "includes/outb.h"


// Fonction pour initialiser le terminal
void s_terminal_initialize(void) {
  s_terminal.row = 0;
  s_terminal.column = 0;
  s_terminal.color = 0x07; // Blanc sur fond noir

  // Effacer le buffer du terminal
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      s_terminal.buffer[index] = (uint16_t) ' ' | (uint16_t) s_terminal.color << 8;
    }
  }
}

// Fonction pour mettre à jour l'affichage du terminal
void s_terminal_update(void) {
  // Copier le buffer du terminal dans l'espace mémoire de l'interface VGA
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      *(uint16_t*) (0xB8000 + 2 * index) = s_terminal.buffer[index];
    }
  }
}

// Fonction pour mettre à jour la position du curseur du terminal
void s_terminal_update_cursor(void) {
  // Calculer la position du curseur dans l'interface VGA
  const uint64_t position = s_terminal.row * VGA_WIDTH + s_terminal.column;

  // Écrire la position du curseur dans les registres de l'interface VGA
  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t) (position & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t) ((position >> 8) & 0xFF));
}

// Fonction pour afficher un caractère sur le terminal
void s_terminal_putchar(char c) {
  // Traiter les retours à la ligne
  if (c == '\n') {
    s_terminal.column = 0;
    if (++s_terminal.row == VGA_HEIGHT) {
      s_terminal.row = 0;
    }
  } else {
    // Calculer l'index du caractère dans le buffer du terminal
    const size_t index = s_terminal.row * VGA_WIDTH + s_terminal.column;
    // Afficher le caractère dans le buffer du terminal
    s_terminal.buffer[index] = (uint16_t) c | (uint16_t) s_terminal.color << 8;
    // Mettre à jour la position du curseur du terminal
    if (++s_terminal.column == VGA_WIDTH) {
      s_terminal.column = 0;
      if (++s_terminal.row == VGA_HEIGHT) {
        s_terminal.row = 0;
      }
    }
  }
}

// Fonction pour effacer le terminal
void s_terminal_clear(void) {
  // Réinitialiser la position du curseur du terminal
  s_terminal.row = 0;
  s_terminal.column = 0;
  // Effacer le buffer du terminal
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      s_terminal.buffer[index] = (uint16_t) ' ' | (uint16_t) s_terminal.color << 8;
    }
  }
}

// Fonction pour définir la couleur du terminal
void s_terminal_set_color(uint8_t color) {
  s_terminal.color = color;
}

// Fonction pour afficher une chaîne de caractères sur le terminal
void s_terminal_putstr(const char* str) {
  // Parcourir la chaîne de caractères et afficher chaque caractère sur le terminal
  for (size_t i = 0; str[i] != '\0'; i++) {
    s_terminal_putchar(str[i]);
  }
}

