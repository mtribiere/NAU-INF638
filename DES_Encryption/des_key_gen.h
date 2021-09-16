#ifndef Des_key_gen_h
#define Des_key_gen_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

unsigned char * generate_key(unsigned char key[], u_int8_t round);
unsigned char * left_bit_shift(unsigned char *key, int length, int shift);
void permutate_array(unsigned char *input_array, unsigned char *output_array, u_int8_t length, u_int8_t perm_box[]);
void print_key_as_bits(unsigned char *key, int length);

#endif
