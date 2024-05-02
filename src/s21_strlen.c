#include "s21_string.h"

s21_size_t s21_strlen(const char* str) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}
