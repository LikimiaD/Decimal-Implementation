#include "../include/decimal.h"

int custom_negate(custom_decimal value, custom_decimal *result) {
  int error = 0;
  if (result) {
    value.bits[3] = value.bits[3] ^ ((unsigned int)1 << 31);
    *result = value;
  } else {
    error = 1;
  }
  return error;
}

int custom_truncate(custom_decimal value, custom_decimal *result) {
  int error = 0;
  if (result) {
    uint64_t rem = 0;
    uint64_t num = 0;
    int scale = get_scale(value);

    while (scale > 0) {
      for (int i = 2; i > -1; i--) {
        num = value.bits[i];
        num += rem << 32;
        rem = num % 10;
        num /= 10;
        value.bits[i] = num;
      }
      scale--;
      rem = 0;
      num = 0;
    }
    set_scale(&value, 0);
    *result = value;
  } else {
    error = 1;
  }
  return error;
}

int custom_floor(custom_decimal value, custom_decimal *result) {
  int error = 0;
  if (result) {
    custom_decimal trunc_value = {0};
    custom_decimal fraction = {0};
    custom_decimal zero_dec = {0};
    custom_truncate(value, &trunc_value);
    custom_sub(value, trunc_value, &fraction);
    if (value.bits[3] >> 31) {
      custom_negate(fraction, &fraction);
      if (!custom_is_greater(fraction, zero_dec)) {
        int_add_decimal(trunc_value, -1, &trunc_value);
      }
    }
    *result = trunc_value;
  } else {
    error = 1;
  }
  return error;
}

int custom_round(custom_decimal value, custom_decimal *result) {
  int error = 0;
  if (result) {
    custom_decimal five = {{5, 0, 0, 0}};
    custom_decimal trunc_value = {0};
    custom_decimal fraction = {0};
    set_scale(&five, 1);
    custom_truncate(value, &trunc_value);
    custom_sub(value, trunc_value, &fraction);
    if (get_bit(value, 127)) {
      custom_negate(fraction, &fraction);
      if (custom_is_greater_or_equal(fraction, five)) {
        int_add_decimal(trunc_value, -1, &trunc_value);
      }
    } else {
      if (custom_is_greater_or_equal(fraction, five)) {
        int_add_decimal(trunc_value, 1, &trunc_value);
      }
    }
    *result = trunc_value;
  } else {
    error = 1;
  }
  return error;
}
