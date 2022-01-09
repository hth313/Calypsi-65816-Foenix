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

// ----------------------------------------------------------------------
//
// Define code and data model used. This is to add a bit of safety in
// case the way a file is assembled is combined with the wrong run-time.
//
// ----------------------------------------------------------------------

#if defined(__CALYPSI_DATA_MODEL_SMALL__)
              .rtmodel dataModel,"small"
#elif defined (__CALYPSI_DATA_MODEL_MEDIUM__)
              .rtmodel dataModel,"medium"
#elif defined(__CALYPSI_DATA_MODEL_LARGE__)
              .rtmodel dataModel,"large"
#elif defined(__CALYPSI_DATA_MODEL_HUGE__)
              .rtmodel dataModel,"huge"
#else
#pragma GCC error "unexpected data model"
#endif

#if defined(__CALYPSI_CODE_MODEL_SMALL__)
              .rtmodel codeModel,"small"
#elif defined(__CALYPSI_CODE_MODEL_LARGE__)
              .rtmodel codeModel,"large"
#else
#pragma GCC error "unexpected code model"
#endif

#endif // __CALYPSI_CODE_MODEL_SMALL__
#endif // __CALYPSI_ASSEMBLER__
#endif // __MACROS_H
