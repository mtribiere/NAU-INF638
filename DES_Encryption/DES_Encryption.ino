const char plaintext[] = "HelloDES!";

const uint8_t ip_permtab[] PROGMEM = {                               
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
    array[position/8] |= (0x01 << position%8);
  }else{
    array[position/8] &= (0xFE << position%8);
  }

}

int getBitAtPosition(uint8_t *array, int position){
  return (array[(position/8)] & (1 << position%8)) ? 1 : 0;
}
 

void setup() {

  /////////////////////////Initial permutation
  //For Left side
  uint8_t currentByte = 0;
  int LnIndex = 0;
  int RnIndex = 0;
  
  for(int i = 0;i<32;i++){
    currentByte = (currentByte << 1) + ((plaintext[ip_permtab[i/8]] & 1 << (ip_permtab[i]%8)) ? 1 : 0);

    if(!(i%8) && i>0){
        Ln[LnIndex] = currentByte;
        LnIndex++; 
    }
    
  }
  
  for(int i = 32;i<64;i++){
    
  }
  
  //CODE HERE
  

}

void loop() {


}
