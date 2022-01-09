// Provide alternative memset() that makes use of VDMA if appropriate.

#include <stdlib.h>
#include <string.h>
#include "foenix/dma.h"
#include "support.h"

#if defined(__CALYPSI_TARGET_65816__) && defined(__CALYPSI_DATA_MODEL_SMALL__)
void *__memset__far (__far void *s, int c, size_t n) {
#else
void *memset (void *s, int c, size_t n) {
#endif
  if (in_vram(s)) {

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

    wait_for_DMA_to_finish();

  } else {

    __attribute__((far)) unsigned char *p = (__attribute__((far)) unsigned char *)s;
    while (n-- > 0) *p++ = c;

  }
  return s;
}
