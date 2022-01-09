#include "macros.h"

              .section code
              .public DMA_wait_delay
DMA_wait_delay:                     ; 6 cycles jsr
              nop                   ; 4 cycles
              nop
              return                ; 6 cycles rts
                                    ; 16 cycles total
