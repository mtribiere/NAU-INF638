#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const uint8_t position[8] = {128, 64, 32, 16, 8, 4, 2, 1};

void permutate_array(uint8_t *input_array, uint8_t *output_array, uint8_t length, const uint8_t perm_box[]);
void print_key_as_bits(uint8_t *key, int length);

#endif
