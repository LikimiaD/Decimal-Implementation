#ifndef DECIMAL_H
#define DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -79228162514264337593543950335.0F
#define MAX_SCALE 28
#define MAX_FLOAT 1.0E-28
#define custom_INF 1.0 / 0.0
#define custom_NAN 0.0 / 0.0
#define MINUS 0x80000000  // 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000  // 00000000 11111111 00000000 00000000

typedef struct {
  unsigned int bits[4];
} custom_decimal;

typedef struct {
  unsigned sign;
  int scale;
  unsigned int bits[8];
} custom_big_decimal;

// decimal_support.c
int get_before_scale(custom_decimal dec);
void normalization(custom_decimal *dec_one, custom_decimal *dec_two);
void equalization(int ext_big, int ext_small, custom_decimal *big_ext,
                  custom_decimal *small_ext);
int multiplay_by_ten(custom_decimal dec, custom_decimal *res);
int division_by_ten(custom_decimal dec, custom_decimal *res);
unsigned int set_mask(int index);
unsigned int get_bit(custom_decimal val, int bit);
void set_bit(custom_decimal *dec, int bit, int value);
void set_sign(custom_decimal *dec, int n);
int get_sign(custom_decimal dec);
int get_scale(custom_decimal dec);
void set_scale(custom_decimal *dec, int value);
int addition(custom_big_decimal value1, custom_big_decimal value2,
             custom_big_decimal *res);
int substraction(custom_big_decimal big_value, custom_big_decimal small_value,
                 custom_big_decimal *res);
unsigned get_bit_bigdecimal(custom_big_decimal val, int bit);
void set_bit_bigdecimal(custom_big_decimal *dec, int bit, int value);
int take_one_to_sub(custom_big_decimal *val, int i);
void transfer_decimal_to_big_decimal(custom_decimal *dec,
                                     custom_big_decimal *big_decimal);
int comparison_mantiss(custom_big_decimal val_1, custom_big_decimal val_2);
void normalization_bigdec(custom_big_decimal *first_value,
                          custom_big_decimal *second_value);
int multiplication_by_ten_bigdec(custom_big_decimal dec,
                                 custom_big_decimal *res);
int division_by_ten_bigdec(custom_big_decimal dec, custom_big_decimal *res);
int check_zero_value(custom_decimal *dec);
int transfer_bigdecimal_to_decimal(custom_big_decimal *big_dec,
                                   custom_decimal *dec);
int reduction_bigdec(custom_big_decimal *dec);
int check_bigdec(custom_big_decimal dec);
int custom_decimal_is_zero(custom_decimal dec);
void shift_left_mantissa(custom_big_decimal *dec);
void shift_left_num_bigdecimal(custom_big_decimal *dec, int num);
int multiplication(custom_big_decimal value_1, custom_big_decimal value_2,
                   custom_big_decimal *res);
int int_add_decimal(custom_decimal dec, int a, custom_decimal *res);
int diff_mantiss(custom_big_decimal val_1, custom_big_decimal val_2);
int comparison_decimal_mantiss(custom_decimal dec1, custom_decimal dec2);
custom_decimal check_minus_null(custom_decimal dec);

// decimal_arithmetic.c
int custom_add(custom_decimal value_1, custom_decimal value_2,
               custom_decimal *result);
int custom_sub(custom_decimal value_1, custom_decimal value_2,
               custom_decimal *result);
int custom_mul(custom_decimal value_1, custom_decimal value_2,
               custom_decimal *result);
int custom_div(custom_decimal value_1, custom_decimal value_2,
               custom_decimal *result);

// decimal_rounding.c
int custom_negate(custom_decimal value, custom_decimal *result);
int custom_truncate(custom_decimal value, custom_decimal *result);
int custom_round(custom_decimal value, custom_decimal *result);
int custom_floor(custom_decimal value, custom_decimal *result);

// decimal_comparison.c
int custom_is_less(custom_decimal dec1, custom_decimal dec2);
int custom_is_less_or_equal(custom_decimal dec1, custom_decimal dec2);
int custom_is_greater(custom_decimal dec1, custom_decimal dec2);
int custom_is_greater_or_equal(custom_decimal dec1, custom_decimal dec2);
int custom_is_equal(custom_decimal dec1, custom_decimal dec2);
int custom_is_not_equal(custom_decimal dec1, custom_decimal dec2);

// decimal_parser.c
int custom_from_int_to_decimal(int src, custom_decimal *dst);
int custom_from_float_to_decimal(float src, custom_decimal *dst);
int custom_from_decimal_to_int(custom_decimal src, int *dst);
int custom_from_decimal_to_float(custom_decimal src, float *dst);

#endif