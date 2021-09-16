#include "des_key_gen.h"

unsigned char position[8] = {128, 64, 32, 16, 8, 4, 2, 1};

u_int8_t key_perm_C0[28] = {56, 48, 40, 32, 24, 16, 8, 0,
                            57, 49, 41, 33, 25, 17, 9, 1,
                            58, 50, 42, 34, 26, 18, 10, 2,
                            59, 51, 43, 35};

u_int8_t key_perm_D0[28] = {62, 54, 46, 38, 30, 22, 14,
                            6, 61, 53, 45, 37, 29, 21,
                            13, 5, 60, 52, 44, 36, 28,
                            20, 12, 4, 27, 19, 11, 3};

u_int8_t key_perm_box_2[48] = {13, 16, 10, 23, 0, 4,
                               2, 27, 14, 5, 20, 9,
                               22, 18, 11, 3, 25, 7,
                               15, 6, 26, 19, 12, 1,
                               40, 51, 30, 36, 46, 54,
                               29, 39, 50, 44, 32, 47,
                               43, 48, 38, 55, 33, 52,
                               45, 41, 49, 35, 28, 31};
u_int8_t shift_array[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void print_key_as_bits(unsigned char *key, int length) {
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
    printf(" ");
  }

  printf("\n");
}

void permutate_array(unsigned char *input_array, unsigned char *output_array, u_int8_t length, u_int8_t perm_box[]) {
  u_int8_t newpos;
  u_int8_t desired_bit;

  for (u_int8_t i = 0; i < length; i++) {
    newpos = i;
    desired_bit = input_array[int(perm_box[i]/8)] & position[perm_box[i]%8];

    if (desired_bit != 0) {
      desired_bit = position[newpos%8];
      output_array[i/8] = desired_bit ^ output_array[i/8];
    }
  }
}

unsigned char * left_bit_shift(unsigned char *key, int length, int shift) {
  unsigned char *shifted_array = (unsigned char *) malloc (length);

  for (u_int8_t i = 0; i < length; i++) {
    shifted_array[i] = key[i];
  }

  unsigned char bits1 = 0, bits2 = shifted_array[0];
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

unsigned char * generate_key(unsigned char key[], u_int8_t round) {
  unsigned char *C0 = (unsigned char *) malloc (4);
  unsigned char *D0 = (unsigned char *) malloc (4);

  permutate_array(key, C0, 28, key_perm_C0);
  permutate_array(key, D0, 28, key_perm_D0);

  unsigned char *C_prev = C0;
  unsigned char *D_prev = D0;

  unsigned char *Ci = NULL;
  unsigned char *Di = NULL;

  for (u_int8_t i = 0; i < round; i++) {
    Ci = left_bit_shift(C_prev, 4, shift_array[i]);
    Di = left_bit_shift(D_prev, 4, shift_array[i]);

    free(C_prev);
    free(D_prev);

    C_prev = Ci;
    D_prev = Di;
  }

  unsigned char * cd_array = (unsigned char *) malloc (7);

  for (u_int8_t j = 0; j < 7; j++) {
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

  unsigned char * new_key = (unsigned char *) malloc (48);
  permutate_array(cd_array, new_key, 48, key_perm_box_2);

  free(cd_array);

  return new_key;
}

int main (int argc, char *argv[]) {
  u_int8_t round = 10;
  unsigned char initial_key[8] = {'B', 'a', 'N', 'A', 'n', 'a', '6', '4'};

  print_key_as_bits(initial_key, 8);

  unsigned char * new_key;
  new_key = generate_key(initial_key, round);

  print_key_as_bits(new_key, 6);

  free(new_key);
}
