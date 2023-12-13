#include <stdlib.h>
#include <string.h>
#include "foenix/dma.h"
#include "support.h"

void *memset_dma (void *s, int c, uint32_t n) {
  if (in_vram(s)) {

    // Enable VDMA
    VDMA_CONTROL_REG = VDMA_CTRL_Enable | SDMA_CTRL0_TRF_Fill;

    VDMA_DST_ADDY = s;

    VDMA_BYTE_2_WRITE = c;
    VDMA_SIZE = n;

    // Start VDMA
    VDMA_CONTROL_REG |= VDMA_CTRL_Start_TRF;

    // When started, the 65816 is held, but it takes a few cycles.
    // Provide a short delay to ensure that we do not execute too far
    // before the transfer actually starts. Call a delay subroutine for
    // this.
    DMA_wait_delay();

    wait_for_VDMA_to_finish();

  } else {

    // Enable VDMA
    SDMA_CTRL_REG0 = SDMA_CTRL0_Enable | SDMA_CTRL0_SysRAM_Src | SDMA_CTRL0_TRF_Fill;

    SDMA_DST_ADDY = s;

    SDMA_BYTE_2_WRITE = c;
    SDMA_SIZE = n;

    // Start SDMA
    SDMA_CTRL_REG0 |= SDMA_CTRL0_Start_TRF;

    // When started, the 65816 is held, but it takes a few cycles.
    // Provide a short delay to ensure that we do not execute too far
    // before the transfer actually starts. Call a delay subroutine for
    // this.
    DMA_wait_delay();

    wait_for_SDMA_to_finish();
  }
  return s;
}
