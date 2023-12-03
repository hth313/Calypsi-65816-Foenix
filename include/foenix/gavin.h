#ifndef __C256_GAVIN_H__
#define __C256_GAVIN_H__

//#include <foenix/interrupt.h>
//#include <foenix/joystick.h>
//#include <foenix/rtc.h>
#include <foenix/system.h>
//#include <foenix/timer.h>
//#include <foenix/uart.h>

struct CompleteGavin {
  union {
    struct _SystemControl system_control;
    char _skip_system_control[0x8];
  };

#if 0
  union {
    struct _RTC rtc;
    char _skip_rtc[0x80];
  };

  union {
    struct _InterruptController interrupt_controller;
    char _skip_interrupt_controller[0x100];
  };

  union {
    struct _Timer timer;
    char _skip_timer[0x100];
  };

  char _skip_sdc[0x100];      // TBD

  char _skip_ide[0x100];      // TBD

  union {
    struct _Joystick joystick;
    char _skip_joystick[0x2800 - 0x0500];
  };

  char _skip_ps2[0xf8];       // TBD

  struct _UART uart;
#endif
};

// Vicky base address has been set up by C startup.
#define _CompleteGavin (* (volatile struct CompleteGavin __far *)0xafe880)

#define SystemControl        _CompleteGavin.system_control
//#define RTC                  _CompleteGavin.rtc
//#define InterruptController  _CompleteGavin.interrupt_controller
//#define Timer                _CompleteGavin.timer
//#define Joystick             _CompleteGavin.joystick
//#define UART                 _CompleteGavin.uart

#endif // __C256_GAVIN_H__
