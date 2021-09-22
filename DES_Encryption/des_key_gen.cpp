#include "des_key_gen.h"

uint8_t * left_bit_shift(uint8_t *key, int length, int shift) {
  uint8_t *shifted_array = (uint8_t *) malloc (length);

  for (uint8_t i = 0; i < length; i++) {
    shifted_array[i] = key[i];
  }

  uint8_t bits1 = 0, bits2 = shifted_array[0];
  for(int i = length-1; i >= 0; i--) {
    bits1 = shifted_array[i] & 0xFF;
    shifted_array[i] <<= shift;
    shifted_array[i] |= bits2 >> (8 - shift);
    if ((i == length - 1) & (shifted_array[i] & 0x07)) {
      shifted_array[i] |= shifted_array[i] << 4;
      shifted_array[i] &= 240;
    }
    bits2 = bits1;
  }
  return shifted_array;
}

uint8_t * generate_key(uint8_t key[], uint8_t round) {
  uint8_t *C0 = (uint8_t *) malloc (4);
  uint8_t *D0 = (uint8_t *) malloc (4);

  for (int i = 0; i < 4; i++) {
    C0[i] = 0;
    D0[i] = 0;
  }

  permutate_array(key, C0, 28, key_perm_C0);
  permutate_array(key, D0, 28, key_perm_D0);

  uint8_t *C_prev = C0;
  uint8_t *D_prev = D0;

  uint8_t *Ci = NULL;
  uint8_t *Di = NULL;

  for (uint8_t i = 0; i < round; i++) {
    Ci = left_bit_shift(C_prev, 4, shift_array[i]);
    Di = left_bit_shift(D_prev, 4, shift_array[i]);

    free(C_prev);
    free(D_prev);

    C_prev = Ci;
    D_prev = Di;
  }

  uint8_t * cd_array = (uint8_t *) malloc (7);

  for (uint8_t j = 0; j < 7; j++) {
    if (j < 3) {
      cd_array[j] = Ci[j];
    }
    else if (j == 3) {
      char combine_byte = ((Ci[3]&240) | (Di[0] >> 4));
      cd_array[3] = combine_byte;
    }
    else if (j > 3) {
      cd_array[j] |= Di[j%4] << 4 | Di[j%4 + 1] >> 4;
    }
  }

  free(Ci);
  free(Di);

  uint8_t * new_key = (uint8_t *) malloc (6);
  for (int i = 0; i < 6; i++) {
    new_key[i] = 0;
  }
  permutate_array(cd_array, new_key, 48, key_perm_box_2);

  free(cd_array);

  return new_key;
}
/*
int main (int argc, char *argv[]) {
  uint8_t round = 1;
  uint8_t initial_key[8] = {0x1B, 0x02, 0xEF, 0xFC, 0x70, 0x72, 0xF5, 0x10};

  print_key_as_bits(initial_key, 8);

  uint8_t * new_key;
  new_key = generate_key(initial_key, round);

  print_key_as_bits(new_key, 6);

  free(new_key);
}*/
