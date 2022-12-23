#ifndef __TERMINAL__H__
#define __TERMINAL__H__

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Structure de données pour représenter le terminal

struct s_terminal {
  size_t row;
  size_t column;
  uint8_t color;
  uint16_t buffer[VGA_WIDTH * VGA_HEIGHT];
};

// Terminal global
struct s_terminal s_terminal;

void s_terminal_update(void);
void s_terminal_update_cursor(void);
void s_terminal_initialize(void);
void s_terminal_putchar(char c);
void s_terminal_clear(void);
void s_terminal_set_color(uint8_t color);
void s_terminal_putstr(const char* str);
#endif
