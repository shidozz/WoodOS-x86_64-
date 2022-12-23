#ifndef __VGA__H__
#define __VGA__H__
// Taille de l'écran en pixels
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Adresse de la mémoire vidéo VGA
#define VGA_MEMORY 0xA0000

// Couleurs prédéfinies
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LIGHT_GRAY 7
#define COLOR_DARK_GRAY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

// Structure représentant un pixel de l'écran
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel;

void draw_pixel(int x, int y, Pixel pixel);
void draw_pixel_color(int x, int y, uint8_t color);
void update_screen();
void drawRectangle(int x, int y, int width, int height, uint8_t color);
void drawFilledRectangle(int x, int y, int width, int height, Pixel color);
void drawCircle(int xc, int yc, int radius, Pixel color);
void drawDiamond(int x, int y, int size, uint8_t color);
void drawCrosshair(int x, int y, int size, uint8_t color);
#endif