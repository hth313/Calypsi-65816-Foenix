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

// ----------------------------------------------------------------------
//
// VDMA
//
// ----------------------------------------------------------------------

typedef struct vdma {
  uint8_t control;
  union {
    uint8_t status;    // read
    uint8_t fill;      // write - fill byte
  };
  vram_ptr src;
  vram_ptr dst;
  union {
    uint32_t size;     // 1-D, size of transfer
    struct {
      uint16_t width;  // 2-D
      uint16_t height; // 2-D
    };
  };
  uint16_t src_stride; // 2-D
  uint16_t dst_stride; // 2-D
} vdma_t;

// Control bits
#define VDMA_CTRL_Enable     0x01 // Enabled the VDMA transfer block
#define VDMA_CTRL_1D_2D      0x02 // 0 - 1D (Linear) Transfer
                                  // 1 - 2D (Block) Transfer
#define VDMA_CTRL_TRF_Fill   0x04 // 0 - Transfer Src -> Dst
                                  // 1 - Fill Destination with "Byte2Write"
#define VDMA_CTRL_Int_Enable 0x08 // Set to 1 to Enable the Generation of
                                  // Interrupt when the Transfer is over.
#define VDMA_CTRL_SysRAM_Src 0x10 // Set to 1 to Indicate that the Source
                                  // is the System Ram Memory
#define VDMA_CTRL_SysRAM_Dst 0x20 // Set to 1 to Indicate that the Destination
                                  // is the System Ram Memory
#define VDMA_CTRL_Start_TRF  0x80 // Set to 1 To Begin Process, Need to Cleared
                                  // before, you can start another

// Status bits (read)
#define VDMA_STAT_Size_Err    0x01 // If Set to 1, Overall Size is Invalid
#define VDMA_STAT_Dst_Add_Err 0x02 // If Set to 1, Destination Address Invalid
#define VDMA_STAT_Src_Add_Err 0x04 // If Set to 1, Source Address Invalid
#define VDMA_STAT_VDMA_IPS    0x80 // If Set to 1, VDMA Transfer in Progress.
                // Do not attempt to access VRAM while a VDMA is in progress!

#endif // __VICKY_H__
