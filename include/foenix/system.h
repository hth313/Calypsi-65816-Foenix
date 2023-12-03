// C256 System control registers
//
// These controls LEDs, buzzer, LFSR (pseudo random number) and holds
// identity values about the machine.

#ifndef __C256_SYSTEM_H__
#define __C256_SYSTEM_H__

#include <stdint.h>

struct _SystemControl {
  union {
    struct {
      uint8_t power_led         : 1;
      uint8_t sd_led            : 1;
      uint8_t                   : 2;
      uint8_t buzzer            : 1;
      uint8_t                   : 2;
      uint8_t manual_reset      : 1;
    };
    uint16_t control;
#define POWER_LED      0x01
#define SD_LED         0x02
#define BUZZER         0x10
#define MANUAL_RESET   0x80
  };
  uint8_t reserved;
  uint16_t security_word;
  union {
    uint16_t seed;
    uint16_t random;
  };
  union {
    struct {
      uint8_t lfsr_enable       : 1;
      uint8_t seed_write        : 1;
      uint8_t                   : 5;
      uint8_t lfsr_done         : 1;
    };
    uint8_t lfsr_control;
#define LFSR_ENABLE     0x01
#define SEED_WRITE      0x02
#define LFSR_DONE       0x80
  };
  union {
    struct {
      uint8_t machine_id_0 : 1;
      uint8_t machine_id_1 : 1;
      uint8_t              : 1;
      uint8_t expansion_card_present : 1;
      uint8_t              : 2;
      uint8_t cpua         : 1;
      uint8_t cpux         : 1;
    };
    uint8_t system_status;
  };
};

#include <foenix/gavin.h>

#endif // __C256_SYSTEM_H__
