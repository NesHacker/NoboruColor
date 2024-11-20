#include <gb/gb.h>
#include "data.h"

// Include binary tile graphics data
INCBIN(tile_data, "res/tiledata.bin")

/**
 * Loads graphics tiles into VRAM.
 */
void load_tileset(void) {
  // Load the sprite tiles (Tiles 0 - 127)
  set_tile_data(0x00, 0x80, tile_data, 0x80);
  // Load the shared tiles (Tiles 128 - 255)
  set_tile_data(0x00, 0x80, tile_data + 128 * 16, 0x88);
  // Load the bg only tile data (Tiles 256-383)
  set_tile_data(0x00, 0x80, tile_data + 256 * 16, 0x90);
}
