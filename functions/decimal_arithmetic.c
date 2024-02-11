#include "../include/decimal.h"

static int checkZero(custom_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}

int custom_add(custom_decimal value_1, custom_decimal value_2,
               custom_decimal *result) {
  memset(result, 0, sizeof(custom_decimal));
  int flag = 0;
  custom_big_decimal big_value_1 = {0};
  custom_big_decimal big_value_2 = {0};
  custom_big_decimal big_result = {0};
  transfer_decimal_to_big_decimal(&value_1, &big_value_1);
  transfer_decimal_to_big_decimal(&value_2, &big_value_2);
  normalization_bigdec(&big_value_1, &big_value_2);
  big_result.scale = big_value_1.scale;
  if (big_value_1.sign == big_value_2.sign) {
    addition(big_value_1, big_value_2, &big_result);
    big_result.sign = big_value_1.sign;
  } else if (comparison_mantiss(big_value_1, big_value_2)) {
    substraction(big_value_1, big_value_2, &big_result);
    big_result.sign = big_value_1.sign;
  } else if (comparison_mantiss(big_value_2, big_value_1)) {
    substraction(big_value_2, big_value_1, &big_result);
    big_result.sign = big_value_2.sign;
  }
  flag = transfer_bigdecimal_to_decimal(&big_result, result);
  if (flag && big_result.sign) flag += 1;
  return flag;
}

int custom_sub(custom_decimal value_1, custom_decimal value_2,
               custom_decimal *result) {
  memset(result, 0, sizeof(custom_decimal));
  int flag = 0;
  custom_negate(value_2, &value_2);
  flag = custom_add(value_1, value_2, result);
  if (custom_decimal_is_zero(*result)) {
    result->bits[3] = 0;
  }
  return flag;
}

int custom_mul(custom_decimal value_1, custom_decimal value_2,
               custom_decimal *result) {
  int flag = 0;
  memset(result, 0, sizeof(custom_decimal));
  custom_big_decimal big_value_1 = {0};
  custom_big_decimal big_value_2 = {0};
  custom_big_decimal big_result = {0};
  transfer_decimal_to_big_decimal(&value_1, &big_value_1);
  transfer_decimal_to_big_decimal(&value_2, &big_value_2);
  normalization_bigdec(&big_value_1, &big_value_2);
  big_result.scale = big_value_1.scale;
  multiplication(big_value_1, big_value_2, &big_result);
  big_result.scale *= 2;
  if (big_value_1.sign == big_value_2.sign)
    big_result.sign = 0;
  else if (big_value_1.sign != big_value_2.sign)
    big_result.sign = 1;
  flag = transfer_bigdecimal_to_decimal(&big_result, result);
  if (flag && big_result.sign) flag += 1;
  return flag;
}

int custom_div(custom_decimal value_1, custom_decimal value_2,
               custom_decimal *result) {
  memset(result, 0, sizeof(custom_decimal));
  int flag = 0;
  if (checkZero(value_2)) {
    flag = 3;
  } else {
    custom_big_decimal big_value_1 = {0};
    custom_big_decimal big_value_2 = {0};
    custom_big_decimal big_result = {0};
    transfer_decimal_to_big_decimal(&value_1, &big_value_1);
    transfer_decimal_to_big_decimal(&value_2, &big_value_2);
    normalization_bigdec(&big_value_1, &big_value_2);
    big_result.scale = big_value_1.scale;
    if (big_value_1.sign == big_value_2.sign) {
      addition(big_value_1, big_value_2, &big_result);
      big_result.sign = big_value_1.sign;
    } else if (comparison_mantiss(big_value_1, big_value_2)) {
      substraction(big_value_1, big_value_2, &big_result);
      big_result.sign = big_value_1.sign;
    } else if (comparison_mantiss(big_value_2, big_value_1)) {
      substraction(big_value_2, big_value_1, &big_result);
      big_result.sign = big_value_2.sign;
    }
    flag = transfer_bigdecimal_to_decimal(&big_result, result);
    if (flag && big_result.sign) flag += 1;
  }
  return flag;
}
