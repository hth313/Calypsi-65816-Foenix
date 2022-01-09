#ifndef __VICKY_H__
#define __VICKY_H__

#include <stdint.h>

#define __vram __far

typedef uint8_t __far24 * vram_ptr;

#define in_vram(addr) ((((unsigned short)(((unsigned long)(addr)) >> 16)) & 0xff) >= 0xb0)

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
// Bitmap plane
//
// ----------------------------------------------------------------------

typedef struct bitmap_plane {
  uint8_t  control;
  vram_ptr start;
  uint8_t  x_offset;
  uint8_t  y_offset;
  uint16_t reserved;
} bitmap_plane_t;

// There are two bitmap planes., use them as bitmap[n].field
// where n is 0-1.
#define bitmap_plane ((bitmap_plane_t __far *)0xaf0100)

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

// Video DMA
#define vdma ((vdma_t __far *)0xaf0400)

// 24-bit color
typedef struct color24 {
  uint8_t  blue;
  uint8_t  green;
  uint8_t  red;
} color24_t;

// ----------------------------------------------------------------------
//
// Vicky
//
// ----------------------------------------------------------------------

typedef struct vicky {
  uint16_t  master_control;
  uint8_t   gamma_control;
  uint8_t   reserved_01;
  uint8_t   border_control;
  color24_t border_color;
  uint8_t   border_width;
  uint8_t   border_height;
  uint8_t   reserved_02[3];
  color24_t background_color;
  uint8_t   cursor_control;
  uint8_t   test_start;
  char      cursor;
  uint8_t   cursor_color;
  uint16_t  cursor_x;
  uint16_t  cursor_y;
  uint32_t  line_interrupt_control;  // bit 0 = line0, bit 1 = line1
  union {
    uint16_t vicky_chip_num;    // read
    uint16_t line0_cmp_value;   // write
  };
  union {
    uint16_t vicky_chip_version;
    uint16_t line1_cmp_value;   // write
  };
} vicky_t;

// Vicky registers
#define vicky ((vicky_t __far *)0xaf0000)

// Modes
#define Mstr_Ctrl_Text_Mode__Lo_En  0x01        Enable the Text Mode
#define Mstr_Ctrl_Text_Overlay      0x02   // Enable the Overlay of the text mode
                                           // on top of Graphic Mode
                                           // (the Background Color is ignored)
#define Mstr_Ctrl_Graph_Mode_En     0x04   // Enable the Graphic Mode
#define Mstr_Ctrl_Bitmap_En         0x08   // Enable the Bitmap Module In Vicky
#define Mstr_Ctrl_TileMap_En        0x10   // Enable the Tile Module in Vicky
#define Mstr_Ctrl_Sprite_En         0x20   // Enable the Sprite Module in Vicky
#define Mstr_Ctrl_GAMMA_En          0x40   // Enable the GAMMA correction
                                           // The Analog and DVI have different color values,
                                           // the GAMMA is great to correct the difference
#define Mstr_Ctrl_Disable_Vid       0x80   // This will disable the Scanning of the Video
                                           // information in the 4Meg of VideoRAM hence giving
                                           // 100% bandwidth to the CPU

#endif // __VICKY_H__
