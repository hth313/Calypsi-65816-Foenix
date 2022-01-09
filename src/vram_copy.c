// Provide alternative memcpy() that makes use of VDMA if appropriate.

#include <stdlib.h>
#include <string.h>
#include "foenix/dma.h"
#include "support.h"

#if defined(__CALYPSI_TARGET_65816__) && defined(__CALYPSI_DATA_MODEL_SMALL__)
void *__memcpy__far (__far void *dest, __far const void *src, size_t n) {
#else
void *memcpy (void *dest, const void *src, size_t n) {
#endif
  if (in_vram(dest)) {

    SDMA_SRC_ADDY = src;
    VDMA_DST_ADDY = dest;

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
    wait_for_DMA_to_finish();

  } else {

    unsigned char *pout = (unsigned char *)dest;
    unsigned char *pin  = (unsigned char *)src;
    while (n-- > 0) *pout++ = *pin++;

  }
  return dest;
}
