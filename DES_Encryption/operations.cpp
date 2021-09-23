#include "operations.h"

void print_key_as_bits(uint8_t *key, int length) {
  char char_to_print;
  for (int i = 0; i < length; i++)
  {
    char_to_print = key[i];

    for (int bit = 0; bit < 8; bit++)
    {
      if (char_to_print & 128) {
        printf("1");
      }
      else {
        printf("0");
      }
      char_to_print <<= 1;
    }
    // printf(" ");
  }

  printf("\n");
}

void permutate_array(uint8_t *input_array, uint8_t *output_array, uint8_t length, const uint8_t perm_box[]) {
  uint8_t desired_bit = 0;

  for (uint8_t i = 0; i < length; i++) {
    desired_bit = input_array[int(perm_box[i]/8)] & position[perm_box[i]%8];

    if (desired_bit != 0) {
      desired_bit = position[i%8];
      output_array[i/8] = desired_bit ^ output_array[i/8];
    }
  }
}
