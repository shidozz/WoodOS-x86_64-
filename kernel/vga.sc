#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "includes/vga.h"
#include "includes/math.h"


// Tableau de pixels de l'écran
static Pixel screen[SCREEN_WIDTH][SCREEN_HEIGHT];

// Fonction de dessin d'un pixel à l'écran
void draw_pixel(int x, int y, Pixel pixel) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        screen[x][y] = pixel;
    }
}

// Fonction de dessin d'un pixel à l'écran avec une couleur prédéfinie
void draw_pixel_color(int x, int y, uint8_t color) {
    Pixel pixel;
    pixel.red = (color & 1) ? 255 : 0;
    pixel.green = (color & 2) ? 255 : 0;
    pixel.blue = (color & 4) ? 255 : 0;
    draw_pixel(x, y, pixel);
}

// Fonction de mise à jour de l'écran
void update_screen() {
  uint16_t* vga_memory = (uint16_t*)VGA_MEMORY;
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      Pixel pixel = screen[x][y];
      uint8_t color = (pixel.red & 128) | ((pixel.green & 128) >> 1) | ((pixel.blue & 128) >> 2);
      vga_memory[y * SCREEN_WIDTH + x] = (color << 8) | color;
    }
  }
}

// Fonction de dessin d'un rectangle à l'écran
void drawFilledRectangle(int x, int y, int width, int height, Pixel color) {
  for (int i = x; i < x + width; i++) {
    for (int j = y; j < y + height; j++) {
      draw_pixel(i, j, color);
    }
  }
}

// Fonction de dessin d'un cercle à l'écran
void drawCircle(int xc, int yc, int radius, Pixel color) {
  for (int x = xc - radius; x <= xc + radius; x++) {
    for (int y = yc - radius; y <= yc + radius; y++) {
      if (sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc)) <= radius) {
        draw_pixel(x, y, color);
      }
    }
  }
}

void drawRectangle(int x, int y, int width, int height, uint8_t color) {
  for (int i = x; i < x + width; i++) {
    draw_pixel_color(i, y, color);
    draw_pixel_color(i, y + height - 1, color);
  }
  for (int i = y; i < y + height; i++) {
    draw_pixel_color(x, i, color);
    draw_pixel_color(x + width - 1, i, color);
  }
}

void drawCrosshair(int x, int y, int size, uint8_t color) {
  // Dessine la ligne horizontale du croisillon
  for (int i = x - size; i <= x + size; i++) {
    draw_pixel_color(i, y, color);
  }

  // Dessine la ligne verticale du croisillon
  for (int j = y - size; j <= y + size; j++) {
    draw_pixel_color(x, j, color);
  }
}

void drawDiamond(int x, int y, int size, uint8_t color) {
  for (int i = 0; i < size; i++) {
    int offset = size - 1 - i;
    draw_pixel_color(x + offset, y + i, color);
    draw_pixel_color(x + i, y + offset, color);
    draw_pixel_color(x - offset, y - i, color);
    draw_pixel_color(x - i, y - offset, color);
  }
}

