#ifndef __FOENIX_INTERRUPT_CONTROLLER_H__
#define __FOENIX_INTERRUPT_CONTROLLER_H__

#include <stdint.h>

typedef struct InterruptController {
  union {
    struct {
      uint8_t startOfFrame      : 1;
      uint8_t startOfLine       : 1;
      uint8_t timer0            : 1;
      uint8_t timer1            : 1;
      uint8_t timer2            : 1;
      uint8_t rtc               : 1;
      uint8_t floppy            : 1;
      uint8_t mouse             : 1;
    };
    uint8_t reg0;
  };
  union {
    struct {
      uint8_t keyboard          : 1;
      uint8_t spriteCollision   : 1;
      uint8_t bitmapCollision   : 1;
      uint8_t serial2           : 1;
      uint8_t serial1           : 1;
      uint8_t midi              : 1;
      uint8_t parallel          : 1;
      uint8_t sd                : 1;
    };
    uint8_t reg1;
  };
  union {
    struct {
      uint8_t opl3              : 1;
      uint8_t gabe0             : 1;
      uint8_t gabe1             : 1;
      uint8_t vdma              : 1;
      uint8_t tileCollision     : 1;
      uint8_t gabe2             : 1;
      uint8_t externalExpansion : 1;
      uint8_t sdInsert          : 1;
    };
    uint8_t reg2;
  };
  union {
    struct {
      uint8_t opn2              : 1;
      uint8_t opm               : 1;
      uint8_t ide               : 1;
      uint8_t                   : 1;
      uint8_t                   : 1;
      uint8_t                   : 1;
      uint8_t                   : 1;
      uint8_t                   : 1;
    };
    uint8_t reg3;
  };
} InterruptController_t;

// Interrupt mask register. A bit value of 0 enables an interrupt,
// a value of 1 disables it.
#define InterruptMask      ( * (volatile InterruptController_t *) 0x00014c )

// Interrupt pending register. A value of 1 indicates that an interrupt
// is pending. Writing a 1 acknowledges the interrupt and resets the bit.
#define InterruptPending   ( * (volatile InterruptController_t *) 0x000140 )

// Trigger on a high or low signal to GABE.
#define InterruptPolarity  ( * (volatile InterruptController_t *) 0x000144 )

// Detect interrupt on edge transition if set to 1, level on 0.
// The kernel initializes these to 1.
#define EdgeDetection      ( * (volatile InterruptController_t *) 0x000148 )

typedef enum InterruptEnable {
  EnabledInterrupt, DisabledInterrupt
} InterruptEnable_t;

#define VectorCOP    (*(void**) 0x00ffe4)
#define VectorBRK    (*(void**) 0x00ffe6)
#define VectorABORT  (*(void**) 0x00ffe8)
#define VectorNMI    (*(void**) 0x00ffea)
#define VectorIRQ    (*(void**) 0x00ffee)

#endif // __FOENIX_INTERRUPT_CONTROLLER_H__
