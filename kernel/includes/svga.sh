#ifndef __SVGA__H__
#define __SVGA__H__
// Taille de l'écran en pixels
#define SVGA_SCREEN_WIDTH 800
#define SVGA_SCREEN_HEIGHT 600

// Adresse de la mémoire vidéo VGA
#define SVGA_MEMORY 0xA0000

// Structure représentant un pixel de l'écran
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel;
#endif