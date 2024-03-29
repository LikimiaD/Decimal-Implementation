#include "../include/decimal.h"

int custom_is_greater(custom_decimal dec_1, custom_decimal dec_2) {
  int res = 0;
  if (!custom_decimal_is_zero(dec_1) && !custom_decimal_is_zero(dec_2)) {
    if (get_bit(dec_1, 127) < get_bit(dec_2, 127)) {
      res = 1;
    } else if (get_bit(dec_1, 127) > get_bit(dec_2, 127)) {
      res = 0;
    } else {
      normalization(&dec_1, &dec_2);
      for (int i = 95; i > -1; i--) {
        if (get_bit(dec_1, i) > get_bit(dec_2, i)) {
          if (!get_bit(dec_1, 127)) {
            res = 1;
          }
          break;
        } else if (get_bit(dec_1, i) < get_bit(dec_2, i)) {
          if (get_bit(dec_1, 127)) {
            res = 1;
          }
          break;
        }
      }
    }
  }
  return res;
}

int custom_is_equal(custom_decimal dec_1, custom_decimal dec_2) {
  int res = 0;
  normalization(&dec_1, &dec_2);
  if (dec_1.bits[0] == dec_2.bits[0] && dec_1.bits[1] == dec_2.bits[1] &&
      dec_1.bits[2] == dec_2.bits[2] && dec_1.bits[3] == dec_2.bits[3]) {
    res = 1;
  }
  return res;
}

int custom_is_not_equal(custom_decimal dec_1, custom_decimal dec_2) {
  return !custom_is_equal(dec_1, dec_2);
}

int custom_is_greater_or_equal(custom_decimal dec_1, custom_decimal dec_2) {
  return (custom_is_equal(dec_1, dec_2) || custom_is_greater(dec_1, dec_2) ? 1
                                                                           : 0);
}

int custom_is_less(custom_decimal dec_1, custom_decimal dec_2) {
  return (custom_is_equal(dec_1, dec_2) || custom_is_greater(dec_1, dec_2) ? 0
                                                                           : 1);
}

int custom_is_less_or_equal(custom_decimal dec_1, custom_decimal dec_2) {
  return (custom_is_equal(dec_1, dec_2) || custom_is_less(dec_1, dec_2) ? 1
                                                                        : 0);
}
