
#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  Flags f = {0};
  va_list va;
  va_start(va, format);
  int totalLength = 0;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      totalLength++;
      continue;
    } else {
      format++;
      s21_memset(&f, 0, sizeof(Flags));
    }

    if (is_flag(*format)) {
      format = get_flags(format, &f);
    }
    if (is_digit(*format) || *format == '*') {
      format = get_width(format, &f, va);
    }
    if (is_digit(*format) || *format == '.' || *format == '*') {
      format = get_precision(format, &f, va);
    }
    if (is_spec(*format)) {
      format = get_length(format, &f);
    }

    f.specifier = *format;
    format++;

    char buff[BUFFER_SIZE] = {'\0'};
    handle_value(&f, buff, va);
    for (int i = 0; buff[i]; i++, str++) *str = buff[i];
    totalLength += s21_strlen(buff);
  }

  *str = '\0';
  va_end(va);
  return totalLength;
}

const char *get_flags(const char *format, Flags *f) {
  while (is_flag(*format)) {
    switch (*format) {
      case '-':
        f->minus = 1;
        break;
      case '+':
        f->plus = 1;
        break;
      case ' ':
        f->space = 1;
        break;
      case '#':
        f->sharp = 1;
        break;
      case '0':
        f->zero = 1;
        break;
      case '.':
        f->tochka = 1;
        break;
    }
    format++;
  }
  return format;
}

const char *get_width(const char *format, Flags *f, va_list va) {
  switch (*format) {
    case '*':
      format++;
      f->width = va_arg(va, int);
      break;
    default:
      f->width = atoi(format);
      while (isdigit(*format)) {
        format++;
      }
      break;
  }
  return format;
}

const char *get_length(const char *format, Flags *f) {
  switch (*format) {
    case 'l':
      f->length = 'l';
      format++;
      break;
    case 'L':
      f->length = 'L';
      format++;
      break;
    case 'h':
      f->length = 'h';
      format++;
      break;
  }
  return format;
}

const char *get_precision(const char *format, Flags *f, va_list va) {
  switch (*format) {
    case '.':
      f->tochka = true;
      format++;
      if (isdigit(*format) || *format == 'f') {
        f->precision = atoi(format);
        while (isdigit(*format)) {
          format++;
        }
        break;
      }
      break;
    case '*':
      f->precision = va_arg(va, int);
      break;
  }
  return format;
}

int handle_value(Flags *f, char *buff, va_list va) {
  int res = 0;
  int64_t num = 0;

  char *temp = calloc(1000 + f->width + 2, sizeof(char));
  switch (f->specifier) {
    case 's': {
      format_s(temp, va, f);
      s21_strcpy(buff, temp);
      res += s21_strlen(buff);
      break;
    }

    case '%': {
      buff[0] = '%';
      break;
    }

    case 'd': {
      if (f->length != 'l' && f->specifier == 'd' && f->length != 'L')
        num = (int)va_arg(va, int);
      if ((f->length == 'l' || f->length == 'L') && f->specifier == 'd')
        num = (int64_t)va_arg(va, int64_t);
      if (f->length == 'h' && f->specifier != 'd') num = (short)va_arg(va, int);
      format_number(temp, num, f);
      s21_strcpy(buff, temp);
      res += s21_strlen(buff);
      break;
    }

    case 'c': {
      char c = va_arg(va, int);
      int width = f->width;
      if (width > 1) {
        buff[0] = c;
        buff[1] = '\0';
        handle_width(width, buff, f);
      } else {
        buff[0] = c;
        buff[1] = '\0';
      }
      res += s21_strlen(buff);
      break;
    }
    case 'f': {
      if (f->length == 'L') {
        long double long_double_num = va_arg(va, long double);
        char temp[BUFFER_SIZE] = {0};
        int precision = f->tochka ? f->precision : 6;
        fltoa(long_double_num, temp, precision, f);
        s21_strcpy(buff, temp);
        handle_width(f->width, buff, f);
        res += (int)s21_strlen(buff);
      }
      if (f->length == 'l') {
        double double_num = (double)va_arg(va, double);
        char temp[BUFFER_SIZE] = {0};
        int precision = f->tochka ? f->precision : 6;
        ftoa(double_num, temp, precision, f);
        s21_strcpy(buff, temp);
        handle_width(f->width, buff, f);
        res += (int)s21_strlen(buff);
      }
      if (f->length == 0) {
        double float_num = va_arg(va, double);
        char temp_str[BUFFER_SIZE] = {0};
        int precision = f->tochka ? f->precision : 6;
        ftoa(float_num, temp_str, precision, f);
        s21_strcpy(buff, temp_str);
        handle_width(f->width, buff, f);
        res += (int)s21_strlen(buff);
      }
      break;
    }

    case 'p': {
      void *ptr = va_arg(va, void *);
      pointer_to_str(ptr, temp, f->width);
      s21_strcpy(buff, temp);
      handle_width(f->width, buff, f);
      res += s21_strlen(buff);
      break;
    }

    case 'o': {
      int num = va_arg(va, int);
      char temp[21] = {0};
      itoa(num, temp, f, 8);
      s21_strcpy(buff, temp);
      handle_width(f->width, buff, f);
      res += s21_strlen(buff);
      break;
    }

    case 'x': {
      int num = va_arg(va, int);
      char temp[21] = {0};
      itoa(num, temp, f, 16);
      s21_strcpy(buff, temp);
      handle_width(f->width, buff, f);
      res += s21_strlen(buff);
      break;
    }

    case 'X': {
      int num = va_arg(va, int);
      char temp[21] = {0};
      itoa(num, temp, f, 16);
      for (int i = 0; temp[i]; i++) {
        temp[i] = toupper(temp[i]);
      }
      s21_strcpy(buff, temp);
      handle_width(f->width, buff, f);
      res += s21_strlen(buff);
      break;
    }

    case 'u': {
      unsigned int num = va_arg(va, unsigned int);
      char temp[21] = {0};
      utoa(num, temp, 10);
      s21_strcpy(buff, temp);
      handle_width(f->width, buff, f);
      res += s21_strlen(buff);
      break;
    }
  }
  free(temp);
  return res;
}

char *utoa(unsigned int number, char *buffer, int base) {
  char symbols[] = "0123456789abcdef";
  int i = 0;
  do {
    buffer[i++] = symbols[number % base];
    number /= base;
  } while (number != 0);
  buffer[i] = '\0';
  reverse(buffer, i);
  return buffer;
}

char *itoa(long long int num, char *str, Flags *f, s21_size_t base) {
  if (str == NULL) {
    return NULL;
  }
  long long int i = 0;
  bool isNegative = false;

  if (num == 0 && !f->tochka) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  if (num < 0 && base == 10) {
    isNegative = true;
    num = -num;
  }

  while (num != 0) {
    long long int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  if (isNegative) str[i++] = '-';

  str[i] = '\0';

  int start = 0;
  int end = (int)i - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }

  return str;
}

void ftoa(double num, char *str, int precision, Flags *f) {
  if (num < 0) {
    *str++ = '-';
    num = -num;
    f->neg = true;
  }
  long int int_part =
      (precision == 0) ? (long int)round_to(num, precision) : (long int)num;
  double frac_part = num - int_part;
  int len_int = 0;
  long int int_for_while = int_part;

  if (((f->plus || f->space) && !f->neg) && num >= 0) {
    *str++ = (f->plus) ? '+' : ' ';
  }

  while (int_for_while != 0) {
    int_for_while /= 10;
    len_int++;
  }
  if (f->plus)
    len_int += precision + 2;
  else
    len_int += precision + 1;

  len_int = f->width - len_int;
  if (!f->minus && f->zero) {
    for (int i = 0; i < len_int; ++i) {
      *str++ = '0';
    }
  }

  s21_sprintf(str, "%ld", int_part);
  str += s21_strlen(str);
  if (f->sharp) {
    *str++ = '.';
  }
  if (precision > 0) {
    if (!f->sharp) *str++ = '.';
    for (int i = 0; i < precision; ++i) {
      frac_part *= 10;
      if (fmod(frac_part, 10.0) > 5)
        frac_part += 4.8 * powl(10, -precision);
      else
        frac_part += 4 * powl(10, -precision);
      int digit = (int)frac_part;
      *str++ = '0' + digit;
      frac_part -= digit;
    }

    *str = '\0';
  } else {
    *str = '\0';
  }
}

void fltoa(long double num, char *str, int precision, Flags *f) {
  if (num < 0) {
    *str++ = '-';
    num = -num;
    f->neg = true;
  }
  long int int_part =
      (precision == 0) ? (long int)round_to(num, precision) : (long int)num;
  long double frac_part = num - int_part;
  int len_int = 0;
  long int int_for_while = int_part;

  if (((f->plus || f->space) && !f->neg) && num >= 0) {
    *str++ = (f->plus) ? '+' : ' ';
  }

  while (int_for_while != 0) {
    int_for_while /= 10;
    len_int++;
  }
  if (f->plus)
    len_int += precision + 2;
  else
    len_int += precision + 1;

  len_int = f->width - len_int;
  if (!f->minus && f->zero) {
    for (int i = 0; i < len_int; ++i) {
      *str++ = '0';
    }
  }

  s21_sprintf(str, "%Ld", int_part);
  str += s21_strlen(str);
  if (f->sharp) {
    *str++ = '.';
  }
  if (precision > 0) {
    if (!f->sharp) *str++ = '.';
    for (int i = 0; i < precision; ++i) {
      frac_part *= 10;
      if (fmodl(frac_part, 10.0L) > 5)
        frac_part += 4.8 * powl(10, -precision);
      else
        frac_part += 4 * powl(10, -precision);
      long int digit = (long int)frac_part;
      *str++ = '0' + digit;
      frac_part -= digit;
    }
    *str = '\0';
  } else {
    *str = '\0';
  }
}

long double round_to(long double value, int precision) {
  long double scale = powl(10, precision);
  return roundl(value * scale) / scale;
}

void pointer_to_str(void *ptr, char *str, int width) {
  uintptr_t iptr = (uintptr_t)ptr;
  int i;
  int pos = 0;
  str[pos++] = '0';
  str[pos++] = 'x';
  width -= 2;  // Уменьшаем ширину на 2, так как мы уже добавили два символа
  for (i = sizeof(uintptr_t) * 8 - 4; i >= 0; i -= 4) {
    int hexDigit = (iptr >> i) & 0xf;
    if (hexDigit != 0 || pos > 2) {
      if (hexDigit < 10) {
        str[pos++] = '0' + hexDigit;
      } else {
        str[pos++] = 'a' + (hexDigit - 10);
      }
    }
  }
  str[pos] = '\0';
}

void reverse(char *str, int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    end--;
    start++;
  }
}

void handle_width(int width, char *buff, Flags *f) {
  int len = s21_strlen(buff);
  if (f->minus) {  // Check if the "-" flag is set
    while (len < width) {
      buff[len] = ' ';
      len++;
    }
    buff[len] = '\0';  // Add the null character after the last space
  } else {
    if (f->zero && f->specifier != 'f') {  // Check if the "0" flag is set
      while (len < width) {
        s21_memmove(buff + 1, buff, len + 1);
        buff[0] = '0';
        len++;
      }
    } else {
      while (len < width) {
        s21_memmove(buff + 1, buff, len + 1);
        buff[0] = ' ';  // Add a space at the beginning of the string
        len++;
      }
    }
    if (((f->zero && f->plus && (f->specifier == 'c' && !f->plus)))) {
      for (s21_size_t i = 0; i < s21_strlen(buff); i++) {
        if (is_digit(buff[i]) && !f->zero) {
          buff[len - 1] = '+';
          len++;
          break;
        }
        if (buff[0] == '0') buff[0] = '+';
      }
    }
  }
}

void format_s(char *temp, va_list va, Flags *f) {
  char *ptr = va_arg(va, char *);
  int srat = 0;
  if (!ptr) {
    ptr = calloc(1000 + f->width, sizeof(char));
    s21_strcat(ptr, "(null)");
    srat = 1;
  }
  char valve = (f->zero) ? '0' : ' ';
  size_t indent = !(f->tochka) ? s21_strlen(ptr) : (size_t)f->precision;
  for (size_t i = 0; i < indent; i++) {
    temp[i] = ptr[i];
  }
  size_t arg_len = s21_strlen(temp);
  size_t width = (arg_len > (size_t)f->width) ? 0 : f->width - arg_len;
  if (f->minus) {
    for (size_t i = s21_strlen(temp), j = 0; j < width; i++, j++) {
      temp[i] = valve;
      temp[f->tochka + f->width + 1] = '\0';
    }
    temp[indent + width + 1] = '\0';
  }
  if (f->plus || !f->minus) {
    for (size_t i = 0; i < width; i++) {
      temp[i] = valve;
    }
    for (size_t i = width, j = 0; j < indent; i++, j++) {
      temp[i] = ptr[j];
    }
    temp[indent + width + 1] = '\0';
  }
  if (srat) free(ptr);
}

void format_number(char *temp, int64_t num, Flags *f) {
  char *ptr = NULL;

  ptr = calloc(10000 + f->width + 5, sizeof(char));
  char *bebra = NULL;
  bebra = calloc(10000 + f->width + 5, sizeof(char));
  itoa(num, ptr, f, 10);
  int arg_len = 0;
  int ptr_len = s21_strlen(ptr);
  if (f->plus || !f->minus) {
    arg_len = (num < 0) ? ptr_len - 2 : ptr_len;
    f->precision = (f->precision > arg_len) ? f->precision - arg_len : 0;
    size_t k = 0;
    int flag = 0;
    if (f->plus && num >= 0) {
      *temp++ = '+';
    }
    if ((num < 0 && !f->zero) || (!f->width && num < 0) ||
        (f->tochka && num < 0)) {
      s21_strcat(bebra, "-");
      k++;
      flag = 1;
    }
    for (; k < (size_t)f->precision; k++) {
      bebra[k] = '0';
    }
    for (size_t i = s21_strlen(bebra), j = 0; j < s21_strlen(ptr); j++, i++) {
      if (ptr[j] == '-') j++;
      bebra[i] = ptr[j];
    }
    arg_len = s21_strlen(bebra);
    f->width = (f->width > arg_len) ? f->width - arg_len : 0;
    int i = 0;
    if (f->zero && num < 0 && !f->tochka && !flag) {
      s21_strcat(temp, "-");
      i++;
    }
    for (; i < f->width; i++) {
      char valve = (f->zero) ? '0' : ' ';
      temp[i] = valve;
    }

    s21_strcat(temp, bebra);
    temp[s21_strlen(temp)] = '\0';
  }
  if (f->minus) {
    arg_len = (num < 0) ? ptr_len - 1 : ptr_len;
    f->precision = (f->precision > arg_len) ? f->precision - arg_len : 0;
    if (num < 0) {
      s21_strcat(temp, "-");
    }
    for (size_t i = 0; i < (size_t)f->precision; i++) {
      bebra[i] = '0';
    }
    s21_strcat(temp, bebra);
    size_t str_len = ptr_len;
    arg_len = s21_strlen(temp);
    for (size_t i = arg_len, j = 0; j < str_len; i++, j++) {
      if (ptr[j] == '-') {
        j++;
      }
      temp[i] = ptr[j];
    }

    arg_len = s21_strlen(temp);
    f->width = (f->width > arg_len) ? f->width - arg_len : 0;
    for (size_t i = arg_len, j = 0; j < (size_t)f->width; j++, i++) {
      temp[i] = ' ';
    }
    temp[s21_strlen(temp)] = '\0';
  }
  free(ptr);
  free(bebra);
}
