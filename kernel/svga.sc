#include <stdint.h>
#include <stddef.h>
#include "includes/svga.h"

// Tableau de pixels de l'écran
static Pixel screen[SVGA_SCREEN_WIDTH][SVGA_SCREEN_HEIGHT];

// Fonction de dessin d'un pixel à l'écran
void draw_pixel(int x, int y, Pixel pixel) {
    if (x >= 0 && x < SVGA_SCREEN_WIDTH && y >= 0 && y < SVGA_SCREEN_HEIGHT) {
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
  uint32_t* svga_memory = (uint32_t*)SVGA_MEMORY;
  for (int y = 0; y < SVGA_SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SVGA_SCREEN_WIDTH; x++) {
      Pixel pixel = screen[x][y];
      uint8_t red = pixel.red;
      uint8_t green = pixel.green;
      uint8_t blue = pixel.blue;
      uint32_t color = (red << 16) | (green << 8) | blue;
      svga_memory[y * SVGA_SCREEN_WIDTH + x] = color;
    }
  }
}
