#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *token;
  if (str == NULL) {
    str = token;
  }
  char *tmp = str;
  int i = 0;
  int j = 0;
  int flag = 0;

  while (*tmp != '\0' && s21_strcspn(tmp, delim) == 0) {
    str++;
    tmp++;
  }
  if (tmp[0] != '\0') {
    while (*tmp != '\0' && flag != 1) {
      j = 0;
      while (delim[j] != '\0' && flag != 1) {
        if (*tmp == delim[j]) {
          str[i] = '\0';
          flag = 1;
        }
        j++;
      }
      i++;
      tmp++;
    }
  } else
    str = s21_NULL;
  token = tmp;
  return str;
}