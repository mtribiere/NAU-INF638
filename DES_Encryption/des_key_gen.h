#ifndef Des_key_gen_h
#define Des_key_gen_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "operations.h"

const uint8_t key_perm_C0[28] = {56, 48, 40, 32, 24, 16, 8, 0,
                                 57, 49, 41, 33, 25, 17, 9, 1,
                                 58, 50, 42, 34, 26, 18, 10, 2,
                                 59, 51, 43, 35};

const uint8_t key_perm_D0[28] = {62, 54, 46, 38, 30, 22, 14,
                                 6, 61, 53, 45, 37, 29, 21,
                                 13, 5, 60, 52, 44, 36, 28,
                                 20, 12, 4, 27, 19, 11, 3};

const uint8_t key_perm_box_2[48] = {13, 16, 10, 23, 0, 4,
                                    2, 27, 14, 5, 20, 9,
                                    22, 18, 11, 3, 25, 7,
                                    15, 6, 26, 19, 12, 1,
                                    40, 51, 30, 36, 46, 54,
                                    29, 39, 50, 44, 32, 47,
                                    43, 48, 38, 55, 33, 52,
                                    45, 41, 49, 35, 28, 31};
const uint8_t shift_array[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

uint8_t * generate_key(uint8_t key[], uint8_t round);
uint8_t * left_bit_shift(uint8_t *key, int length, int shift);

#endif
