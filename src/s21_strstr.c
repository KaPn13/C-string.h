#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  int i = 0;
  int z = 0;
  s21_size_t x = 0;
  int stop = 0;
  if (*needle != '\0') {
    while (haystack[i] != '\0' && result == s21_NULL) {
      z = i;
      x = 0;
      stop = 0;
      if (haystack[i] == needle[x]) {
        while (haystack[z] != '\0' && needle[x] != '\0' && stop == 0) {
          if (haystack[z] != needle[x]) {
            stop = 1;
          } else {
            z++;
            x++;
          }
          if (x == s21_strlen(needle) && stop != 1)
            result = (char *)&haystack[i];
        }
      }
      i++;
    }
  } else
    result = (char *)haystack;
  return result;
}
