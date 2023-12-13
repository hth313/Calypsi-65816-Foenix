// Provide alternative memcpy() that makes use of VDMA if appropriate.

#include <stdlib.h>
#include <string.h>
#include <foenix/dma.h>
#include <foenix/vicky.h>
#include "support.h"

#if defined(__CALYPSI_TARGET_65816__) && defined(__CALYPSI_DATA_MODEL_SMALL__)
__far void *__memcpy_far (void __far *dest, const __far void *src, size_t n) {
#else
void *memcpy (void *dest, const void *src, size_t n) {
#endif
  return memcpy_dma(dest, src, n);
}
