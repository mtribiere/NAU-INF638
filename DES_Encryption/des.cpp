
#include "des.h"



uint8_t *desEncryption(uint8_t *plaintext, uint8_t *original_key) {
  uint8_t Ln[4];
  uint8_t Rn[4];
  uint8_t Rn_prev[4];
  uint8_t *ffunction_res;
  uint8_t *key;

  uint8_t *result = (uint8_t *) malloc (8);
  for (int i = 0; i < 8; i++) {
    result[i] = 0;
  }

  uint8_t tempPerm[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  permutate_array(plaintext, tempPerm, 64, ip_permtab);

  memcpy(Ln, tempPerm, 4);
  memcpy(Rn, tempPerm+4, 4);

  for (int i = 1; i <= 16; i++) {
    memcpy(Rn_prev, Rn, 4);

    key = generate_key(original_key, i);

    ffunction_res = ffunction(Rn, key);
    free(key);

    for (int j = 0; j < 4; j++) {
      Rn[j] = Ln[j] ^ ffunction_res[j];
    }
    
    free(ffunction_res);
    memcpy(Ln, Rn_prev, 4);
  }

  for (int i = 0; i < 8; i++) {
    if (i < 4) {
      tempPerm[i] = Rn[i];
    }
    else {
      tempPerm[i] = Ln[i%4];
    }
  }
  permutate_array(tempPerm, result, 64, final_permtab);

  return result;
}

uint8_t * desDecryption(uint8_t *cyphertext, uint8_t *original_key) {
  uint8_t Ln[4];
  uint8_t Rn[4];
  uint8_t Rn_prev[4];
  uint8_t *ffunction_res;
  uint8_t *key;

  uint8_t *result = (uint8_t *) malloc (8);
  for (int i = 0; i < 8; i++) {
    result[i] = 0;
  }

  uint8_t tempPerm[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  permutate_array(cyphertext, tempPerm, 64, ip_permtab);

  memcpy(Ln, tempPerm, 4);
  memcpy(Rn, tempPerm+4, 4);

  for (int i = 16; i >= 1; i--) {
    memcpy(Rn_prev, Rn, 4);

    key = generate_key(original_key, i);

    ffunction_res = ffunction(Rn, key);
    free(key);
    
    for (int j = 0; j < 4; j++) {
      Rn[j] = Ln[j] ^ ffunction_res[j];
    }
    
    free(ffunction_res);
    memcpy(Ln, Rn_prev, 4);
  }

  for (int i = 0; i < 8; i++) {
    if (i < 4) {
      tempPerm[i] = Rn[i];
    }
    else {
      tempPerm[i] = Ln[i%4];
    }
  }
  permutate_array(tempPerm, result, 64, final_permtab);

  return result;
}
/*
int main(int argc, char const *argv[]) {
  uint8_t *cyphertext = desEncryption(plaintext, original_key);
  print_key_as_bits(cyphertext, 8);
  uint8_t *decrypted_plaintext = desDecryption(cyphertext, original_key);
  for (int i = 0; i < 8; i++) {
    printf("%c", plaintext[i]);
  }
  printf("\n");
  for (int i = 0; i < 8; i++) {
    printf("%c", decrypted_plaintext[i]);
  }
  printf("\n");
  
  free(cyphertext);
  free(decrypted_plaintext);
  return 0;
}*/
