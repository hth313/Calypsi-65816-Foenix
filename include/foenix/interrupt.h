#ifndef __FOENIX_INTERRUPT_CONTROLLER_H__
#define __FOENIX_INTERRUPT_CONTROLLER_H__

#include <stdint.h>

typedef struct InterruptControllerPending {
  uint8_t reg0;
  uint8_t reg1;
  uint8_t reg2;
  uint8_t reg3;
} InterruptController_t;

// Register 0 bits
#define InterruptStartOfFrame      (1 << 0)
#define InterruptStartOfLine       (1 << 1)
#define InterruptTimer0            (1 << 2)
#define InterruptTimer1            (1 << 3)
#define InterruptTimer2            (1 << 4)
#define InterruptRTC               (1 << 5)
#define InterruptFloppy            (1 << 6)
#define InterruptMouse             (1 << 7)

// Register 1 bits
#define InterruptKeyboard          (1 << 0)
#define InterruptSpriteCollision   (1 << 1)
#define InterruptBitmapCollision   (1 << 2)
#define InterruptSerial2           (1 << 3)
#define InterruptSerial1           (1 << 4)
#define InterruptMIDI              (1 << 5)
#define InterruptParallel          (1 << 6)
#define InterruptSD                (1 << 7)

// Register 2 bits
#define InterruptOPL3              (1 << 0)
#define InterruptGabe0             (1 << 1)
#define InterruptGabe1             (1 << 2)
#define InterruptVdma              (1 << 3)
#define InterruptTileCollision     (1 << 4)
#define InterruptGabe2             (1 << 5)
#define InterruptExternalExpansion (1 << 6)
#define InterruptInsertSD          (1 << 7)

// Register 3 bits
#define InterruptOPN2              (1 << 0)
#define InterruptOPM               (1 << 1)
#define InterruptIDE               (1 << 2)


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
