#ifndef __DMA_H__
#define __DMA_H__

#include <stdint.h>
#include "foenix/vicky.h"

// ----------------------------------------------------------------------
//
// System DMA controller
//
// ----------------------------------------------------------------------

#define SDMA_CTRL_REG0            (*(volatile __vram uint8_t *)0xaf0420)

// SDMA_CTRL_REG0 field bits
#define SDMA_CTRL0_Enable         0x01
#define SDMA_CTRL0_1D_2D          0x02  // 0 - 1D (linear) transfer
                                        // 1 - 2D (block) transfer
#define SDMA_CTRL0_TRF_Fill       0x04  // 0 - transfer src -> dst
                                        // 1 - Fill Destination with "Byte2Write"
#define SDMA_CTRL0_Int_Enable     0x08  // set to 1 to enable the generation of
                                        //   interrupt when the transfer is over
#define SDMA_CTRL0_SysRAM_Src     0x10  // set to 1 to indicate that the source
                                        //   is the system RAM Memory
#define SDMA_CTRL0_SysRAM_Dst     0x20  // set to 1 to indicate that the destination
                                        //   is the system RAM memory

// SDMA_CONTROL_REG0[5:4]
//                   00: SRAM to SRAM Transfer
//                   01: SRAM to VRAM Transfer (SDMA & VDMA needs to be initialized for transfer to work)
//                   10: VRAM to SRAM Transfer (SDMA & VDMA needs to be initialized for transfer to work)
//                   11: IO Transfer from or to SRAM (refer to SDMA_CONTROL_REG1 for config and direction )

#define SDMA_XFER_SRAM2SRAM  0x00  // SRAM -> SRAM transfer
#define SDMA_XFER_SRAM2VRAM  0x10  // SRAM -> VRAM transfer
#define SDMA_XFER_VRAM2SRAM  0x20  // VRAM -> SRAM transfer
#define SDMA_XFER_SRAMIO  0x30  // SRAM <-> IO transfer (see: SDMA_CONTROL_REG1 for config and direction)

#define SDMA_CTLR0_RSVD           0x40  // Reserved
#define SDMA_CTRL0_Start_TRF      0x80  // Set to 1 To Begin Process, Need to Cleared before, you can start another

// THIS SECTION HAS NOT BEEN IMPLEMENTED YET, SO IGNORE FOR NOW
// Control Register to manage the IO Transfer from and to SRAM
#define SDMA_CTRL_REG1            (*(volatile unsigned char *)0xaf0421)  // Write Only - Byte to Write in the Fill Function
#define SDMA_CTRL1_IO_Src         0x01  // 1 = Source is an IO Address (ADC, SuperIO, IDE)
#define SDMA_CTRL1_IO_Src16       0x02  // 0 = Src 8Bits Transfer / 1= 16Bits Transfer
#define SDMA_CTRL1_IO_Dst         0x04  // 1 = Destination is an IO Address (DAC, SuperIO, IDE)
#define SDMA_CTRL1_IO_Dst16       0x08  // 0 = Dst 8bits Transfer / 1= 16bits

// Let me repeat, don't access the video memory then there is a VDMA in progress!

// Pointer to the source of the data to be transfered
// This needs to be within CPU's system RAM range (0x000000 - 0x3fffff)
#define SDMA_SRC_ADDY          (*(volatile const __attribute__((far24)) void * __attribute__((far24)) *)0xaf0422)

// Destination pointer within CPU's video memory range
  // This needs to be within CPU's system RAM range (0x000000 - 0x3fffff)
#define SDMA_DST_ADDY          (*(volatile __attribute__((far24)) void * __attribute__((far24)) *)0xaf0425)

// In 1D transfer mode, maximum Value: 0x400000 (4Megs)
#define SDMA_SIZE              (*(volatile uint32_t *)0xaf0428)

// In 2D transfer mode, maximum Value: 65535
#define SDMA_X_SIZE            (*(volatile uint16_t *)0xaf0428)
#define SDMA_Y_SIZE            (*(volatile uint16_t *)0xaf042a)

// Always use an even number ( the engine uses even version of that value)
#define SDMA_SRC_STRIDE        (*(volatile uint16_t *)0xaf042c)
#define SDMA_DST_STRIDE        (*(volatile uint16_t *)0xaf042e)

// Write Only - byte to write in the fill function
#define SDMA_BYTE_2_WRITE        (*(volatile unsigned char *)0xaf0430)

// Read only
#define SDMA_STATUS_REG          (*(volatile unsigned char *)0xaf0430)

// Status Bit Field Definition
#define SDMA_STAT_Size_Err        0x01  // if set to 1, overall size is invalid
#define SDMA_STAT_Dst_Add_Err     0x02  // if set to 1, destination address invalid
#define SDMA_STAT_Src_Add_Err     0x04  // if set to 1, source address invalid
#define SDMA_STAT_TimeOut_Err     0x08  // will be set to 1 if a timeout occurs
                                        //   when transfering between data from
                                        //   and to VRAM

// ----------------------------------------------------------------------
//
// Video DMA controller
//
// ----------------------------------------------------------------------


#define VDMA_CONTROL_REG         (*(volatile __vram uint8_t *)0xaf0400)

// VDMA_CONTROL_REG field bits
#define VDMA_CTRL_Enable         0x01
#define VDMA_CTRL_1D_2D          0x02  // 0 - 1D (linear) transfer
                                       // 1 - 2D (block) transfer
#define VDMA_CTRL_TRF_Fill       0x04  // 0 - transfer src -> dst
                                       // 1 - fill destination with byte to write
#define VDMA_CTRL_Int_Enable     0x08  // set to 1 to enable the generation of
                                       //   interrupt when the transfer is over
#define VDMA_CTRL_SysRAM_Src     0x10  // set to 1 to Indicate that the source
                                       //   is the system RAM memory
#define VDMA_CTRL_SysRAM_Dst     0x20  // set to 1 to indicate that the destination
                                       //   is the system RAM memory
#define VDMA_CTRL_Start_TRF      0x80  // set to 1 to begin process
                                       //   need to cleared before you can start
                                       //   another transfer

#define VDMA_XFER_VRAM2VRAM  0x00  // VRAM -> VRAM transfer
#define VDMA_XFER_SRAM2VRAM  0x01  // SRAM -> VRAM transfer
#define VDMA_XFER_VRAM2SRAM  0x02  // VRAM -> SRAM transfer

// Write only - byte to write in the fill function
#define VDMA_BYTE_2_WRITE        (*(volatile __vram uint8_t *)0xaf0401)

// read only
#define VDMA_STATUS_REG          (*(volatile __vram uint8_t *)0xaf0401)

// Status bit field definitions
#define VDMA_STAT_Size_Err       0x01  // if set to 1, overall size is invalid
#define VDMA_STAT_Dst_Add_Err    0x02  // if set to 1, destination address invalid
#define VDMA_STAT_Src_Add_Err    0x04  // if set to 1, source address invalid
#define VDMA_STAT_VDMA_IPS       0x80  // if set to 1, VDMA transfer in progress
                                       //    (this Inhibits CPU access to memory)

// Do NOT access the video memory when there is a VDMA in progress!

// Pointer to the source of the data to be transfered.
// This needs to be within Vicky's address range ($00_0000 - $3F_0000)
#define VDMA_SRC_ADDY          (*(volatile __attribute__((far24) void * __attribute__((far24)) *)0xaf0402)

// Destination Pointer within Vicky's video memory Range
// This needs to be within Vicky's address range ($00_0000 - $3F_0000)
#define VDMA_DST_ADDY          (*(volatile __attribute__((far24)) void * __attribute__((far24)) *)0xaf0405)

// In 1D transfer mode, maximum Value: 0x400000 (4 mega bytes)
#define VDMA_SIZE              (*(volatile __vram uint32_t *)0xaf0408)

// In 2D Transfer Mode, maximum Value: 0x400000 (65535 bytes)
#define VDMA_X_SIZE            (*(volatile __vram uint16_t *)0xaf0408)
#define VDMA_Y_SIZE            (*(volatile __vram uint16_t *)0xaf040a)

// Always use an even number
#define VDMA_SRC_STRIDE        (*(volatile __vram uint16_t *)0xaf040c)
#define VDMA_DST_STRIDE        (*(volatile __vram uint16_t *)0xaf040e)

// ----------------------------------------------------------------------
//
// Functions provided for copy and set video memory.
//
// ----------------------------------------------------------------------

#if defined(__CALYPSI_TARGET_65816__) && defined(__CALYPSI_DATA_MODEL_SMALL__)
#define vram_copy __memcpy__far
#define vram_fill __memset__far
#else
#define vram_copy memcpy
#define vram_fill memset
#endif

#endif // __DMA_H__
