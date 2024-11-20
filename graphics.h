#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#define RGB_SKY_BLUE        RGB8(160, 228, 240)
#define RGB_NOBORU_SKIN     RGB8(199, 172, 131)
#define RGB_NOBORU_PURPLE1  RGB8(135, 32, 216)
#define RGB_NOBORU_PURPLE2  RGB8(126, 0, 125)

#define RGB_DIRT_LIGHT      RGB8(186, 134, 43)
#define RGB_DIRT_MEDIUM     RGB8(147, 89, 20)
#define RGB_GRASS_GREEN     RGB8(70, 180, 70)
#define RGB_DIRT_DARK       RGB8(44, 26, 11)

extern const uint16_t paletteBrick[];
extern const uint16_t paletteGround[];

void draw_brick (uint8_t x, uint8_t y);
void draw_level(void);
void load_palettes(void);

#endif