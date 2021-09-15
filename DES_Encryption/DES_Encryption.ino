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

uint8_t Ln[4];
uint8_t Rn[4];

void setBitAtPosition(uint8_t *array, int position, int value){

  if(value){
    array[position/8] |= (0x80 >> position%8);
    Serial.println("Putting 1");
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
  
  /////////////////////////Initial permutation
  uint8_t tempPerm[8];
  permutation(ip_permtab, plaintext, tempPerm, 64);

  memcpy(Ln, tempPerm, 4);
  memcpy(Rn, tempPerm+4, 4);
  
  Serial.println("Ln :");
  for(int i = 0;i<4;i++){
    Serial.println(Ln[i]);
  }
  
  Serial.println("Rn :");
  for(int i = 0;i<4;i++){
    Serial.println(Rn[i]);
  }
  
  //////////////////////////////CODE HERE
  

}

void loop() {


}
