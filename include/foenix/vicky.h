#ifndef __VICKY_H__
#define __VICKY_H__

#include <stdint.h>

#define __vram __far

typedef uint8_t __far24 * vram_ptr;

// ----------------------------------------------------------------------
//
// Tile map
//
// ----------------------------------------------------------------------

typedef struct tilemap {
  uint8_t  control;
  vram_ptr data;
  uint16_t width;
  uint16_t height;
  uint16_t x;
  uint16_t y;
} tilemap_t;

// There are four tilemap register sets, use them as tilemap[n].field
// where n is 0-3.
#define tilemap ((tilemap_t __far *)0xaf0200)

// Bits for control register
#define TILE_Enable       0x01
#define TILE_Collision_On 0x40 /* Enable */

// ----------------------------------------------------------------------
//
// Tile sets
//
// ----------------------------------------------------------------------

typedef struct tileset {
  vram_ptr data;
  uint8_t config;
} tileset_t;

// Adjust video RAM address for Vicky. Video RAM starts at 0xb00000
// but Vicky sees that as address 0.
inline vram_ptr vicky_address (vram_ptr p) {
  return (vram_ptr) ((long)p - 0xb00000);
}

// Tile set configuration bits.
#define TILE_Stride_256    (1 << 3)

// There are eight tileset register sets, use them as tileset[n].field
// where n is 0-7.
#define tileset ((tileset_t __far *)0xaf0280)

// ----------------------------------------------------------------------
//
// Sprites
//
// ----------------------------------------------------------------------

typedef struct sprite {
  union {
    struct {
      uint8_t enable : 1;
      uint8_t lut : 3;
      uint8_t depth : 3;
      uint8_t collisionOn : 1;
    };
    uint8_t control;
  };
  vram_ptr data;
  uint16_t x;
  uint16_t y;
} sprite_t;

// There are 64 sprite register sets, use them as sprite[n].field
// where n is 0-63.
#define sprite ((sprite_t __far *)0xaf0c00)


#endif // __VICKY_H__
