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
    array[position/8] |= (0x80 >> position%8);
  }else{
    array[position/8] &= (0x7F >> position%8);
  }

}

int getBitAtPosition(uint8_t *array, int position){
  return (array[(position/8)] & (0x80 >> position%8)) ? 1 : 0;
}
 

void setup() {
  Serial.begin(9600);
  
  /////////////////////////Initial permutation
  uint8_t testArray[] = {0,0,0,0};

  setBitAtPosition(testArray,30,1);
  Serial.println(getBitAtPosition(testArray,30));
  Serial.println(getBitAtPosition(testArray,31));
    
  for(int i = 0;i<4;i++)
    Serial.println(testArray[i]);
  Serial.println();
  
  //CODE HERE
  

}

void loop() {


}
