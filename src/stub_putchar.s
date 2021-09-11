#include "macros.h"


PUTC:         .equlab 0x1018

              .section libcode
              .public _Stub_putchar
_Stub_putchar:
              and     ##0x00ff      ; zero extend char, we always succeed
              jsl     PUTC
              return
