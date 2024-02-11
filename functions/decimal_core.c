#include "../include/decimal.h"

unsigned int set_mask(int index) { return 1u << (index % 32); }

unsigned int get_bit(custom_decimal val, int bit) {
  unsigned int mask = set_mask(bit);
  return (val.bits[bit / 32] & mask) != 0;
}

void set_bit(custom_decimal *dec, int bit, int value) {
  if (value == 1) {
    dec->bits[bit / 32] |= (set_mask(bit));
  } else if (value == 0) {
    dec->bits[bit / 32] &= ~(set_mask(bit));
  }
}

int get_sign(custom_decimal dec) { return get_bit(dec, 127); }

int get_scale(custom_decimal dec) { return (dec.bits[3] & (255 << 16)) >> 16; }

void set_sign(custom_decimal *dec, int n) { set_bit(dec, 127, n); }

void set_scale(custom_decimal *dec, int value) {
  dec->bits[3] = get_bit(*dec, 127) << 31 | value << 16;
}

int get_before_scale(custom_decimal dec) { return (dec.bits[3] & 32767); }

int int_add_decimal(custom_decimal dec, int a, custom_decimal *res) {
  int error = 0;
  custom_decimal value = {0};
  int sign = (a < 0) ? 1 : 0;
  if (sign) custom_negate(value, &value);
  value.bits[0] = abs(a);
  error = custom_add(dec, value, res);
  return error;
}

void normalization(custom_decimal *dec_one, custom_decimal *dec_two) {
  int ext_one = get_scale(*dec_one);
  int ext_two = get_scale(*dec_two);
  if (ext_one > 28) {
    while (ext_one != 28) {
      division_by_ten(*dec_one, dec_one);
      set_scale(dec_one, --ext_one);
    }
  }
  if (ext_two > 28) {
    while (ext_two != 28) {
      division_by_ten(*dec_two, dec_two);
      set_scale(dec_two, --ext_two);
    }
  }
  int diff = ext_one - ext_two;
  if (diff > 0)
    equalization(ext_one, ext_two, dec_one, dec_two);
  else if (diff < 0)
    equalization(ext_two, ext_one, dec_two, dec_one);
}

void equalization(int ext_big, int ext_small, custom_decimal *big_ext,
                  custom_decimal *small_ext) {
  int diff = ext_big - ext_small;
  custom_decimal tmp = *small_ext;
  int work_mul = 1;
  while (diff > 0 && work_mul) {
    multiplay_by_ten(tmp, &tmp);
    if (get_before_scale(tmp)) work_mul = 0;
    if (work_mul) {
      diff--;
      set_scale(&tmp, ++ext_small);
      *small_ext = tmp;
    }
  }
  while (diff) {
    division_by_ten(*big_ext, big_ext);
    set_scale(big_ext, --ext_big);
    diff--;
  }
}

int multiplay_by_ten(custom_decimal dec, custom_decimal *res) {
  uint64_t tmp_u;
  unsigned int remainder = 0;
  for (int i = 0; i < 3; i++) {
    tmp_u = dec.bits[i];
    tmp_u *= 10;
    tmp_u += remainder;
    remainder = tmp_u >> 32;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  return 0;
}

int division_by_ten(custom_decimal dec, custom_decimal *res) {
  uint64_t tmp_u;
  uint64_t remained = 0;
  for (int i = 2; i > -1; i--) {
    tmp_u = dec.bits[i];
    tmp_u |= remained << 32;
    remained = tmp_u % 10;
    tmp_u /= 10;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  return remained;
}
