#include <errno.h>
#include <stubs.h>

extern void __kernel_putchar(char);

// Can call kernel directly in large code model only.
#ifdef __CALYPSI_CODE_MODEL_SMALL__
#define CHROUT(c) __kernel_putchar(c)
#else
#define CHROUT(c) ( (void (*)(char) ) 0x1018) (c)
#endif

size_t _Stub_write (int fd, const void *buf, size_t count) {
  const char *p = buf;
  size_t n = 0;

  switch (fd) {
  case 1: {
    char c;
    while (count) {
      CHROUT(*p);
      n += 1;
      p += 1;
      count -= 1;
    }
    break;
    }
  default:
    __set_errno(EBADF);
    return (size_t) -1;
  }
  return n;
}
