#include "../include/decimal.h"

int custom_from_int_to_decimal(int src, custom_decimal *dst) {
  int error = 1;
  if (dst) {
    error = 0;
    *dst = (custom_decimal){0};
    dst->bits[0] = abs(src);
    if (src < 0) set_sign(dst, 1);
  }
  return error;
}

int custom_from_decimal_to_int(custom_decimal src, int *dst) {
  int error = 0, res = 0, sign = get_sign(src);
  custom_truncate(src, &src);
  if (src.bits[1] != 0) {
    error = 1;
  } else {
    res = src.bits[0];
    if (sign) res *= -1;
    *dst = res;
  }
  return error;
}

int custom_from_decimal_to_float(custom_decimal src, float *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  } else {
    int scale = get_scale(src);
    long double tmp = 0;
    for (int i = 0; i < 96; i++) tmp += pow(2, i) * get_bit(src, i);
    while (scale != 0) {
      tmp /= 10.0;
      scale--;
    }
    if (get_sign(src)) tmp *= -1.0;
    *dst = tmp;
  }
  return error;
}

int custom_from_float_to_decimal(float src, custom_decimal *dst) {
  int error = 0;
  if (isnan(src) || isinf(src) || fabs(src) > MAX_DECIMAL) error = 1;
  if (dst && !error) {
    for (int i = 0; i < 128; i++) set_bit(dst, i, 0);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = fabs(src);
    }
    int temp = (int)src;
    int scale = 0;
    while (src - ((float)temp / (int)(pow(10, scale))) != 0) {
      scale++;
      temp = src * (int)(pow(10, scale));
    }
    custom_from_int_to_decimal(temp, dst);
    if (sign) custom_negate(*dst, dst);
    set_scale(dst, scale);
  } else {
    error = 1;
  }
  return error;
}