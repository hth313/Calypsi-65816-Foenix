#include <stdlib.h>
#include <string.h>
#include <foenix/dma.h>
#include <foenix/vicky.h>
#include "support.h"

void *memcpy_dma (void *dest, const void *src, uint32_t n) {
  if (in_vram(dest)) {

    // Enable DMA and VDMA
    VDMA_CONTROL_REG = VDMA_CTRL_Enable | VDMA_CTRL_SysRAM_Src;
    SDMA_CTRL_REG0 = SDMA_CTRL0_Enable | SDMA_XFER_SRAM2VRAM;

    SDMA_SRC_ADDY = src;
    VDMA_DST_ADDY = vicky_address(dest);

    SDMA_SIZE = n;
    VDMA_SIZE = n;

    // Start VDMA
    VDMA_CONTROL_REG |= VDMA_CTRL_Start_TRF;
    // Start system DMA
    SDMA_CTRL_REG0 |= SDMA_CTRL0_Start_TRF;

    // When started, the 65816 is held, but it takes a few cycles.
    // Provide a short delay to ensure that we do not execute too far
    // before the transfer actually starts. Call a delay subroutine for
    // this.
    DMA_wait_delay();

    SDMA_CTRL_REG0 = 0;

    wait_for_VDMA_to_finish();

    VDMA_CONTROL_REG = 0;

  } else {

    // Enable DMA and VDMA
    SDMA_CTRL_REG0 = SDMA_CTRL0_Enable | SDMA_XFER_SRAM2SRAM;

    SDMA_SRC_ADDY = src;
    SDMA_DST_ADDY = dest;

    SDMA_SIZE = n;

    // Start system DMA
    SDMA_CTRL_REG0 |= SDMA_CTRL0_Start_TRF;

    // When started, the 65816 is held, but it takes a few cycles.
    // Provide a short delay to ensure that we do not execute too far
    // before the transfer actually starts. Call a delay subroutine for
    // this.
    DMA_wait_delay();

    // As the CPU is stopped during DMA, when we resume it will
    // be done, now disable the DMA.
    SDMA_CTRL_REG0 = 0;
  }
  return dest;
}
