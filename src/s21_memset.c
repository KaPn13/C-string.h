#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *str1 = (unsigned char *)str;
  while (n > 0) {
    *str1 = (unsigned char)c;
    str1++;
    n--;
  }
  return str;
}