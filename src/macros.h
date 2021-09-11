#ifndef __MACROS_H
#define __MACROS_H

#ifdef __CALYPSI_ASSEMBLER__

#ifdef __CALYPSI_CODE_MODEL_SMALL__

#define libcode code

call          .macro  dest
              jsr     \dest
              .endm

return        .macro
              rts
              .endm

jump          .macro  dest
              jmp     \dest
              .endm

#else

#define libcode farcode

call          .macro  dest
              jsl     \dest
              .endm

return        .macro
              rtl
              .endm

jump          .macro  dest
              jmp     long:\dest
              .endm

#endif // __CALYPSI_CODE_MODEL_SMALL__
#endif // __CALYPSI_ASSEMBLER__
#endif // __MACROS_H
