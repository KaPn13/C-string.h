#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *cdest;
  char *csrc;

  cdest = (char *)dest;
  csrc = (char *)src;

  if (dest <= src) {
    while (n--) {
      *cdest++ = *csrc++;
    }
  } else if (dest > src) {
    cdest += n - 1;
    csrc += n - 1;
    while (n--) {
      *cdest-- = *csrc--;
    }
  }
  return (dest);
}
