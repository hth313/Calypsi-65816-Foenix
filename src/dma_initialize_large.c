#pragma rtattr initialize="large"

#include <stddef.h>
#include <stdint.h>
#include <foenix/dma.h>
#include <foenix/vicky.h>
#include "support.h"

struct __init_data {
  __far uint8_t       *dest;
  __far const uint8_t *src;
  uint32_t             size;
};

void __initialize_sections(__far struct __init_data *p,
                           __far struct __init_data *end) {
  while (p < end) {
    __attribute__((far)) uint8_t *dest = p->dest;
    __attribute__((far)) const uint8_t *src = p->src;
    if (src) {
      memcpy_dma(dest, src, p->size);
    } else {
      memset_dma(dest, 0, p->size);
    }
    p++;
  }
}
