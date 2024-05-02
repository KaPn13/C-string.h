#include "s21_string.h"

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  int j = 0;
  int i = 0;
  int flag_s = 0;
  while (str1[i] != '\0' && flag_s != 1) {
    j = 0;
    while (str2[j] != '\0') {
      if (str1[i] == str2[j]) {
        flag_s = 1;
      }
      j++;
    }
    if (flag_s != 1) i++;
  }
  return i;
}