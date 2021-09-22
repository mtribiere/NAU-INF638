#include "ffunction.h"
#include "des_key_gen.h"

// Considering 32-bit input from Ri:
uint8_t r[4] = {0xF0, 0xAA, 0xF0, 0xAA};
uint8_t key[6] = {0x1B, 0x02, 0xEF, 0xFC, 0x70, 0x72, 0xF5, 0x10};

//const char plaintext[] = "HelloDES!";
const uint8_t plaintext[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

const uint8_t ip_permtab[] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17,  9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
};
const uint8_t final_permtab[] = {                                         /* 64 bit -> 64 bit */
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41,  9, 49, 17, 57, 25
};


uint8_t Ln[4];
uint8_t Rn[4];

void setBitAtPosition(uint8_t *array, int position, int value){

  if(value){
    array[position/8] |= (0x80 >> position%8);
  }else{
    array[position/8] &= ~(0x80 >> position%8);
  }

}

int getBitAtPosition(const uint8_t *array, int position){
  return (array[(position/8)] & (0x80 >> position%8)) ? 1 : 0;
}

void permutation(const uint8_t *table, const uint8_t *input, uint8_t *output, int outputSize){

    for(int i = 0;i<outputSize;i++)
      setBitAtPosition(output, i, getBitAtPosition(input,table[i]-1)); //Because FUCKING offset


}

void setup() {
  Serial.begin(9600);

  //Initial permutation
  uint8_t tempPerm[8];
  permutation(ip_permtab, plaintext, tempPerm, 64);

  memcpy(Ln, tempPerm, 4);
  memcpy(Rn, tempPerm+4, 4);

  //Make 16 rounds
  for(int i = 0;i < 16;i++){

    Serial.print("Round");
    Serial.println(i+1);

    //Exexute f function
    uint8_t *tmpKey = generate_key(key,i+1);
    uint8_t *result = malloc(sizeof(uint8_t) * 4);
    result = ffunction(Rn,tmpKey);

    //Apply XOR
    for(int j = 0;j<4;j++)
      result[j] = result[j] ^ Ln[j];

    //Switch results
    memcpy(Ln,Rn,4);
    memcpy(Rn, result, 4);

    //Clean memory
    free(result);
    free(tmpKey);

  }

  //Final permutation
  uint8_t roundResult[4];
  uint8_t finalResult[4];

  memcpy(roundResult,Ln,4);
  memcpy(roundResult+4,Rn,4);

  permutation(final_permtab, roundResult, finalResult, 64);

   for(int i = 0;i<8;i++){
    Serial.print(finalResult[i]);
    Serial.print(" ");
   }

   Serial.println();


  //////////////////////////////CODE HERE


}

void loop() {


}
