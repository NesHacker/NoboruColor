#include "graphics.h"

/**
 * Draws some background tiles to display on the screen.
 */
void draw_brick (uint8_t x, uint8_t y) {
  set_bkg_tile_xy(x, y, 0x86);
  set_bkg_tile_xy(x + 1, y, 0x87);
  set_bkg_tile_xy(x, y + 1, 0x96);
  set_bkg_tile_xy(x + 1, y + 1, 0x97);
}

/**
 * Draws background graphics for the level.
 */
void draw_level(void) {
  // Clear the background and draw some graphics
  VBK_REG = VBK_TILES;
  fill_bkg_rect(0, 0, 31, 31, 0);
  fill_bkg_rect(0, 12, 31, 1, 0x03);
  fill_bkg_rect(0, 13, 31, 1, 0x13);
  fill_bkg_rect(0, 14, 31, 1, 0x02);
  fill_bkg_rect(0, 15, 31, 1, 0x12);
  fill_bkg_rect(0, 16, 31, 3, 0x11);

  // Set the palettes for the background tiles
  VBK_REG = VBK_ATTRIBUTES;
  fill_bkg_rect(0, 0, 31, 12, 0b00000001);
}

const uint16_t paletteBrick[] = {
  RGB_SKY_BLUE,
  RGB_RED,
  RGB_BROWN,
  RGB_BLACK,
};

const uint16_t paletteGround[] = {
  RGB_DIRT_LIGHT,
  RGB_DIRT_MEDIUM,
  RGB_GRASS_GREEN,
  RGB_DIRT_DARK,
};

const uint16_t paletteNoboru[] = {
  RGB_SKY_BLUE,
  RGB_NOBORU_SKIN,
  RGB_NOBORU_PURPLE1,
  RGB_NOBORU_PURPLE2
};

void load_palettes (void) {
  set_bkg_palette(0, 1, paletteGround);
  set_bkg_palette(1, 1, paletteBrick);
  set_sprite_palette(0, 1, paletteNoboru);
}
