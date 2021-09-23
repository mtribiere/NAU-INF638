#include "des.h"

uint8_t plainTextArray[8];
uint8_t original_key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
String plaintext;

void setup() {
  Serial.begin(9600);
  Serial.println("======== Welcome to INF-638 DES encryption ======");
  Serial.println("Waiting for plaintext\n\n\n");

}

void loop() {

    if (Serial.available() > 0) {
    
      // read the incoming byte:
      plaintext = Serial.readString();

      // Say what you got:
      Serial.print("Plaintext : ");
      Serial.println(plaintext);

      //For 8 first bytes
      for(int i = 0;i<8;i++){
        plainTextArray[i] = (byte) plaintext.charAt(i);
      }
    
      Serial.print("DES Encryption started....");
      unsigned long time = micros();
      uint8_t *cyphertext = desEncryption(plainTextArray, original_key);
      time = micros() - time;
      Serial.print("[DONE] -> ");
      for(int i = 0;i<8;i++){
        Serial.print(cyphertext[i],HEX);
        Serial.print(" ");
      }
      Serial.print("(Took ");
      Serial.print(time);
      Serial.println(" microseconds)");

      Serial.print("DES Decryption started....");
      time = micros();
      uint8_t *plaintextDecoded = desDecryption(cyphertext, original_key);
      time = micros() - time;
      Serial.print("[DONE] -> ");
      for(int i = 0;i<8;i++){
        Serial.print((char)plaintextDecoded[i]);
        Serial.print(" ");
      }
      Serial.print("(Took ");
      Serial.print(time);
      Serial.println(" microseconds)");
      
      free(cyphertext);
      free(plaintextDecoded);
      
    }


}
