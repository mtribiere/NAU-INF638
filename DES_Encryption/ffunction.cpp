#include "ffunction.h"

uint8_t* expansionPermutation(uint8_t arr[]) {
  uint8_t *expandedArray = (uint8_t *) malloc (6);
  for (int i = 0; i < 6; i++) {
    expandedArray[i] = 0;
  }

  permutate_array(arr, expandedArray, 48, expansionPermutationTable);
  return expandedArray;
}

uint8_t* sBoxSubstitution(uint8_t *arr) {
  uint8_t *sBoxArray = (uint8_t *) malloc (6);

  uint8_t byte_array1[8] = {252, 3, 15, 63, 252, 3, 15, 63};
  uint8_t byte_array2[8] = {0, 240, 192, 0, 0, 240, 192, 0};
  int8_t byte1_shifts[8] = {2, -4, -2, 0, 2, -4, -2, 0};
  int8_t byte2_shifts[8] = {0, 4, 6, 0, 0, 4, 6, 0};
  uint8_t key_array_idx[8] = {0, 0, 1, 2, 3, 3, 4, 5};

  uint8_t byte1 = 0;
  uint8_t byte2 = 0;
  uint8_t resByte = 0;
  uint8_t firstByte = 0;
  uint8_t secondByte = 0;
  for (int i = 0; i < 8; i++) {
    firstByte = arr[key_array_idx[i]] & byte_array1[i];
    if (byte_array2[i] != 0) {
      secondByte = arr[key_array_idx[i] + 1] & byte_array2[i];
    }
    else {
      secondByte = 0;
    }
    if (byte1_shifts[i] <= 0) {
      byte1 = firstByte << -(byte1_shifts[i]);
    }
    else if(byte1_shifts[i] > 0) {
      byte1 = firstByte >> byte1_shifts[i];
    }
    if (byte2_shifts[i] <= 0) {
      byte2 = secondByte << -(byte2_shifts[i]);
    }
    else if(byte2_shifts[i] > 0) {
      byte2 = secondByte >> byte2_shifts[i];
    }
    resByte = byte1 | byte2;

    byte1 = 0;
    byte2 = 0;

    byte1 = resByte & 0x1E;
    byte2 = resByte & 0x21;

    byte1 >>= 1;
    byte2 = (byte2 >> 4) | (byte2 & 0x01);

    uint8_t newValue = pgm_read_byte(&sboxTable[i][byte2][byte1]);

    if ((i % 2) == 0) {
      newValue <<= 4;
      sBoxArray[int(i/2)] = newValue;
    }
    else if ((i % 2) == 1) {
      sBoxArray[int(i/2)] |= newValue;
    }
  }

  return sBoxArray;
}

uint8_t* pBoxPermutation(uint8_t *arr) {
  uint8_t *permutatedArray = (uint8_t *) malloc (4);
  for (int i = 0; i < 4; i++) {
    permutatedArray[i] = 0;
  }

  permutate_array(arr, permutatedArray, 32, pboxPermutationTable);
  return permutatedArray;
}

uint8_t* ffunction(uint8_t *r, uint8_t *key) {
  // 32-bit input -> Expansion permutation -> 48-bit output
  uint8_t* expandedArray = expansionPermutation(r);

  // 48-bit inputs -> XOR -> 48-bit output
  uint8_t *XORArray = (uint8_t *) malloc (6);
  for (int i = 0; i < 6; i ++) {
    XORArray[i] = expandedArray[i] ^ key[i];
  }
  free(expandedArray);

  // 48-bit input -> S-Box -> 32-bit output
  uint8_t* substitutedArray = sBoxSubstitution(XORArray);
  free(XORArray);

  // 32-bit input -> P-Box permutation -> 32-bit output
  uint8_t* permutatedArray = pBoxPermutation(substitutedArray);
  free(substitutedArray);

  return permutatedArray;
}
/*
int main (int argc, char *argv[]) {
  uint8_t *output = ffunction(r, key);
  print_key_as_bits(output, 4);
}*/
