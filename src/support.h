#ifndef __C256_SUPPORT_H__
#define __C256_SUPPORT_H__

#include <stdint.h>
#include "foenix/dma.h"

extern void DMA_wait_delay(void);

inline void wait_for_VDMA_to_finish(void) {
  while ((VDMA_STATUS_REG & VDMA_STAT_VDMA_IPS))
    ;
  VDMA_CONTROL_REG = 0;
}

#endif // __C256_SUPPORT_H__
