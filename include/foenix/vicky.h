#ifndef __VICKY_H__
#define __VICKY_H__

#include <stdint.h>

typedef uint8_t __far24 * vram_ptr;

#define in_vram(addr) ((((unsigned short)(((unsigned long)(addr)) >> 16)) & 0xff) >= 0xb0)

// ----------------------------------------------------------------------
//
// Internal VICKY Registers and internal memory locations (LUTs)
//
// ----------------------------------------------------------------------

#define MASTER_CTRL_REG  (*(volatile __far uint16_t *)0xaf0000)

#define Mstr_Ctrl_Text_Mode_En   0x0001  // enable the text mode
#define Mstr_Ctrl_Text_Overlay   0x0002  // enable the overlay of the text mode
                                         //   on top of Graphic Mode
                                         //   (the background color is ignored)
#define Mstr_Ctrl_Graph_Mode_En  0x0004  // enable the graphic mode
#define Mstr_Ctrl_Bitmap_En      0x0008  // enable the bitmap module
#define Mstr_Ctrl_TileMap_En     0x0010  // enable the tile module
#define Mstr_Ctrl_Sprite_En      0x0020  // enable the sprite module
#define Mstr_Ctrl_GAMMA_En       0x0040  // this enable the gamma correction
                                         //  - The analog and DVI have different
                                         // color value, the gamma is great
                                         // to correct the difference
#define Mstr_Ctrl_Disable_Vid    0x0080  // disable the scanning of the video,
                                         // hence giving 100% bandwith to the CPU

#define Mstr_Ctrl_Video_Mode0    0x0100  // 0 - 640x480 (Clock @ 25.175Mhz)
                                         // 1 - 800x600 (Clock @ 40Mhz)
#define Mstr_Ctrl_Video_Mode1    0x0200  // 0 - no pixel doubling
                                         // 1- pixel doubling
                                         // (reduce the pixel resolution by 2)

// Reserved - TBD
#define VKY_RESERVED_00          (*(volatile __far uint8_t *)0xaf0002)
#define VKY_RESERVED_01          (*(volatile __far uint8_t *)0xaf0003)
#define Border_Ctrl_Enable       0x01
#define BORDER_CTRL_REG          (*(volatile __far uint8_t *)0xaf0004)  // bit[0] - enable (1 by default)
                                                                        // bit[4..6]: X scroll offset
                                                                        // ( will scroll left) (acceptable value: 0..7)
#define BORDER_COLOR_B           (*(volatile __far uint8_t *)0xaf0005)
#define BORDER_COLOR_G           (*(volatile __far uint8_t *)0xaf0006)
#define BORDER_COLOR_R           (*(volatile __far uint8_t *)0xaf0007)
#define BORDER_X_SIZE            (*(volatile __far uint8_t *)0xaf0008)  // X-  values: 0 - 32 (default: 32)
#define BORDER_Y_SIZE            (*(volatile __far uint8_t *)0xaf0009)  // Y- values 0 -32 (default: 32)

#define BACKGROUND_COLOR_B       (*(volatile __far uint8_t *)0xaf000d)  // when in graphic mode, if a pixel
                                                                        // is "0" then the background pixel is chosen
#define BACKGROUND_COLOR_G       (*(volatile __far uint8_t *)0xaf000e)
#define BACKGROUND_COLOR_R       (*(volatile __far uint8_t *)0xaf000f)

#define VKY_TXT_CURSOR_CTRL_REG  (*(volatile __far uint8_t *)0xaf0010)  // [0] enable text mode
#define Vky_Cursor_Enable        0x01
#define Vky_Cursor_Flash_Rate0   0x02
#define Vky_Cursor_Flash_Rate1   0x04
#define Vky_Cursor_FONT_Page0    0x08  // pick font page 0 or font page 1
#define Vky_Cursor_FONT_Page1    0x10  // pick font page 0 or font page 1
#define VKY_TXT_START_ADD_PTR    ((volatile __far uint8_t *)0xaf0011)  // this is an offset to change the starting address
                                                                       //  of the Text Mode Buffer (in x)
#define VKY_TXT_CURSOR_CHAR_REG  (*(volatile __far uint8_t *)0xaf0012)

#define VKY_TXT_CURSOR_COLR_REG  (*(volatile __far uint8_t *)0xaf0013)
#define VKY_TXT_CURSOR_X_REG     (*(volatile __far uint16_t *)0xaf0014)
#define VKY_TXT_CURSOR_Y_REG     (*(volatile __far uint16_t *)0xaf0016)


// Line Interrupt Registers
#define VKY_LINE_IRQ_CTRL_REG    (*(volatile __far uint8_t *)0xaf001b)   // [0] - enable line 0
                                                                         // [1] -enable line 1
#define VKY_LINE0_CMP_VALUE      (*(volatile __far uint16_t *)0xaf001c)  // write only [11:0]
#define VKY_LINE1_CMP_VALUE      (*(volatile __far uint16_t *)0xaf001e)  // write only [11:0]

// When you Read the Register
#define VKY_INFO_CHIP_NUM        (*(volatile __far uint16_t *)0xaf001c)
#define VKY_INFO_CHIP_VER        (*(volatile __far uint16_t *)0xaf001e)

// Mouse Pointer Graphic Memory
#define MOUSE_PTR_GRAP0_START     (*(volatile __far uint8_t *)0xaf0500)  // 16 x 16 = 256 pixels (grey scale)
                                                                         // 0 = transparent
                                                                         // 1 = black
                                                                         // 255 = white
#define MOUSE_PTR_GRAP0_END       (*(volatile __far uint8_t *)0xaf05ff)  // pointer 0
#define MOUSE_PTR_GRAP1_START     (*(volatile __far uint8_t *)0xaf0600)  //
#define MOUSE_PTR_GRAP1_END       (*(volatile __far uint8_t *)0xaf06ff)  // pointer 1

#define MOUSE_PTR_CTRL_REG        (*(volatile __far uint16_t *)0xaf0700) // bit[0] enable
                                                                         // bit[1] = 0
                                                                         //   ( 0 = pointer0, 1 = pointer1)
#define MOUSE_PTR_X_POS          (*(volatile __far uint16_t *)0xaf0702)  // X position (0 - 639) (can only read now)
                                                                         //   writing will have no effect
#define MOUSE_PTR_Y_POS          (*(volatile __far uint16_t *)0xaf0704)  // Y Position (0 - 479) (can only read now)
                                                                         //   writing will have no effect
#define MOUSE_PTR                (*(volatile vram_ptr *)0xaf0706)        // mouse packet
#define C256F_MODEL_MAJOR        (*(volatile __far uint8_t *)0xaf070b)
#define C256F_MODEL_MINOR        (*(volatile __far uint8_t *)0xaf070c)
#define FPGA_DOR                 (*(volatile __far uint8_t *)0xaf070d)
#define FPGA_MOR                 (*(volatile __far uint8_t *)0xaf070e)
#define FPGA_YOR                 (*(volatile __far uint8_t *)0xaf070f)

#define FG_CHAR_LUT_PTR          ((volatile __far uint8_t *)0xAF1F40)
#define BG_CHAR_LUT_PTR          (*(volatile __far uint8_t *)0xaf1f80)

#define GRPH_LUT0_PTR            (*(volatile __far uint8_t *)0xaf2000)
#define GRPH_LUT1_PTR            (*(volatile __far uint8_t *)0xaf2400)
#define GRPH_LUT2_PTR            (*(volatile __far uint8_t *)0xaf2800)
#define GRPH_LUT3_PTR            (*(volatile __far uint8_t *)0xaf2c00)
#define GRPH_LUT4_PTR            (*(volatile __far uint8_t *)0xaf3000)
#define GRPH_LUT5_PTR            (*(volatile __far uint8_t *)0xaf3400)
#define GRPH_LUT6_PTR            (*(volatile __far uint8_t *)0xaf3800)
#define GRPH_LUT7_PTR            (*(volatile __far uint8_t *)0xaf3c00)

#define GRPH_LUT0_LONG           ((volatile __far uint32_t *)0xaf2000)
#define GRPH_LUT1_LONG           ((volatile __far uint32_t *)0xaf2400)
#define GRPH_LUT2_LONG           ((volatile __far uint32_t *)0xaf2800)
#define GRPH_LUT3_LONG           ((volatile __far uint32_t *)0xaf2c00)
#define GRPH_LUT4_LONG           ((volatile __far uint32_t *)0xaf3000)
#define GRPH_LUT5_LONG           ((volatile __far uint32_t *)0xaf3400)
#define GRPH_LUT6_LONG           ((volatile __far uint32_t *)0xaf3800)
#define GRPH_LUT7_LONG           ((volatile __far uint32_t *)0xaf3c00)

#define GAMMA_B_LUT_PTR          (*(volatile __far uint8_t *)0xaf4000)
#define GAMMA_G_LUT_PTR          (*(volatile __far uint8_t *)0xaf4100)
#define GAMMA_R_LUT_PTR          (*(volatile __far uint8_t *)0xaf4200)

#define FONT_MEMORY_BANK0        (*(volatile __far uint8_t *)0xaf8000)  //$af8000 - $af87ff
#define FONT_MEMORY_BANK1        (*(volatile __far uint8_t *)0xaf8800)  //$af8800 - $af8fff
#define CS_TEXT_MEM_PTR          ((volatile __far uint8_t *)0xafa000)
#define CS_COLOR_MEM_PTR         ((volatile __far uint8_t *)0xafc000)

#define BTX_START                (*(volatile __far uint8_t *)0xafe000)  // Beatrix Registers
#define BTX_END                  (*(volatile __far uint8_t *)0xafffff)

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

typedef struct bitplane {
  uint8_t  control;
  vram_ptr start;
  uint8_t  x_offset;
  uint8_t  y_offset;
  uint16_t reserved;
} bitplane_t;

// There are two bitmap planes, use them as bitplane[n].field
// where n is 0-1.
#define bitplane ((bitplane_t __far *)0xaf0100)

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


#endif // __VICKY_H__
