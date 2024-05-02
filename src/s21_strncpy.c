#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  char *result = s21_NULL;
  while (i < n) {
    dest[i] = src[i];
    i++;
  }
  result = dest;
  return result;
}