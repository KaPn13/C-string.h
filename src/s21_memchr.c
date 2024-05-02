#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *st = (char *)str;
  char *result = s21_NULL;
  char sym = c;
  if (sym != '\0') {
    s21_size_t i = 0;
    while (st[i] != '\0' && i != n && result == s21_NULL) {
      if (st[i] == sym) result = (char *)&st[i];
      i++;
    }
  } else {
    result = (char *)&st[s21_strlen(st)];
  }
  return result;
}