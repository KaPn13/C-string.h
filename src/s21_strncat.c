#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int size = s21_strlen(dest);
  int j = size;
  s21_size_t i = 0;
  while (src[i] != '\0' && i < n) {
    dest[j] = src[i];
    i++;
    j++;
  }
  dest[j] = '\0';  // Добавление завершающего символа
  return dest;
}