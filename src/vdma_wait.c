#include "foenix/dma.h"
#include "support.h"

void wait_for_DMA_to_finish () {
  while ((VDMA_STATUS_REG & VDMA_STAT_VDMA_IPS))
    ;
  VDMA_CONTROL_REG = 0;
}
