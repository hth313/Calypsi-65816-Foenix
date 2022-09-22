#ifndef __FOENIX_TIMER_H__
#define __FOENIX_TIMER_H__

#include <stdint.h>

struct timer_value {
  uint8_t low;
  uint8_t mid;
  uint8_t high;
};

typedef struct timer {
  uint8_t control;
  struct timer_value value;
  union {
    struct {
      uint8_t reload_clear : 1;
      uint8_t reload       : 1;
    };
    uint8_t compare_control;
  };
  struct timer_value compare_value;
} timer_t;

// Use with 'direction' bit
enum timer_direction { CountDown, CountUp };

enum timer_control { TimerEnable = 1, TimerClear = 2, TimerLoad = 4, TimerCountUp = 8, TimerCountDown = 0 };

// There are three timers, use them as timer[n].field,
// where n is 0-2.
#define Timer ((timer_t *)0x0160)

#define SetTimeValue(tv,n)  {  \
  tv.low  = n & 0xff;          \
  tv.mid  = (n >> 8)  & 0xff;  \
  tv.high = (n >> 16) & 0xff;  \
}

#define SystemClockHz 14318180ull
#define MillisToClockValue(millis) ((uint32_t)((SystemClockHz * (millis) + 500) / 1000LL))
#define MicrosToClockValue(micros) ((uint32_t)((SystemClockHz * (micros) + 500000) / 1000000LL))

#endif // __FOENIX_TIMER_H__
