#include "operations.h"

void permutate_array(uint8_t *input_array, uint8_t *output_array, uint8_t length, const uint8_t perm_box[]) {
  uint8_t desired_bit;

  for (uint8_t i = 0; i < length; i++) {
    desired_bit = input_array[int(perm_box[i]/8)] & position[perm_box[i]%8];

    if (desired_bit != 0) {
      desired_bit = position[i%8];
      output_array[i/8] = desired_bit ^ output_array[i/8];
    }
  }
}
