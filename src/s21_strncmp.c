#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  unsigned long i = 0;
  int match = 0;
  int stop = 0;

  while (i < n && stop == 0) {
    if (str1[i] != str2[i]) {
      match = str1[i] - str2[i];
      stop = 1;
    }
    i++;
    if (str1[i] == '\0' && str2[i] == '\0' && stop == 0) {
      match = 0;
      stop = 1;
    }
  }
  return match;
}