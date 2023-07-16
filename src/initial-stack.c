#include <stdint.h>

// Initial stack pointer is saved here when called from the C256 kernel
// and restored by _Stub_exit()
uint16_t _InitialStack;
