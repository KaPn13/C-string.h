#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  char sym = c;
  int i = 0;
  if (sym != '\0') {
    while (str[i] != '\0' && result == NULL) {
      if (str[i] == sym) result = (char *)&str[i];

      i++;
    }
  } else
    result = "\0";
  return result;
}