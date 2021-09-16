#ifndef Des_key_gen_h
#define Des_key_gen_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

u_int8_t * generate_key(u_int8_t key[], u_int8_t round);
u_int8_t * left_bit_shift(u_int8_t *key, int length, int shift);
void permutate_array(u_int8_t *input_array, u_int8_t *output_array, u_int8_t length, u_int8_t perm_box[]);
void print_key_as_bits(u_int8_t *key, int length);

#endif
