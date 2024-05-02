#ifndef S21_STRING_H
#define S21_STRING_H

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define is_flag(x) (x == '-' || x == '+' || x == ' ' || x == '#' || x == '0')

#define is_len(x) (x == 'l' || x == 'L' || x == 'h')

#define is_digit(x)                                                        \
  (x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || \
   x == '7' || x == '8' || x == '9')

#define is_spec(x)                                                         \
  (x == 'c' || x == 'd' || x == 'i' || x == 'e' || x == 'f' || x == 'g' || \
   x == 'o' || x == 's' || x == 'u' || x == 'x' || x == 'p' || x == 'l' || \
   x == 'L' || x == 'h')

#define s21_NULL (void *)0
#define BUFFER_SIZE 10000
typedef long unsigned s21_size_t;

typedef struct {
  int zero;
  int left;
  int plus;
  int minus;
  int space;
  int sharp;
  char length;
  int width;
  int precision;
  char specifier;
  int is_precision;
  int leadingZeros;
  bool tochka;
  bool neg;
} Flags;

// sprintf

int s21_sprintf(char *str, const char *format, ...);

void *s21_memset(void *str, int c, s21_size_t n);
void format_s(char *temp, va_list va, Flags *f);
const char *get_flags(const char *format, Flags *f);
const char *get_width(const char *format, Flags *f, va_list va);
const char *get_length(const char *format, Flags *f);
const char *get_precision(const char *format, Flags *f, va_list va);
void format_number(char *temp, int64_t num, Flags *f);
void handle_width(int width, char *buff, Flags *f);
void fltoa(long double num, char *str, int precision, Flags *f);
void ftoa(double num, char *str, int precision, Flags *f);
void format_s(char *temp_str, va_list arg_list, Flags *f);
void pointer_to_str(void *ptr, char *str, int width);
char *itoa(long long int num, char *str, Flags *f, s21_size_t base);
void reverse(char *str, int length);
char *utoa(unsigned int number, char *buffer, int base);
long double round_to(long double value, int precision);

// function
char *s21_strcat(char *dest, const char *src);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
char *s21_strerror(int errnum);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int handle_value(Flags *f, char *buff, va_list va);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strdup(const char *s);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
void add_spaces(char *dest, unsigned int num_of_spaces);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
s21_size_t s21_strcspn(const char *str1, const char *str2);
void *s21_memchr(const void *str, int c, s21_size_t n);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strtok(char *str, const char *delim);
#endif
