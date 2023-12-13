// Provide alternative memset() that makes use of VDMA if appropriate.

#include <stdlib.h>
#include <string.h>
#include "foenix/dma.h"
#include "support.h"

#if defined(__CALYPSI_TARGET_65816__) && defined(__CALYPSI_DATA_MODEL_SMALL__)
__far void *__memset__far (__far void *s, int c, size_t n) {
#else
void *memset (void *s, int c, size_t n) {
#endif
  return memset_dma(s, c, n);
}
