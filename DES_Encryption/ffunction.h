// Include the header below for using uint8_t - discard/remove if you're using in another import or header file.
#include <cstdint>
#include <cstring>
#include <sstream>
/**
#include <bitset>
// Use for debugging output in sets of 8 (I ordered every table below row-wise in sets of 8 as well)
**/

// Include guards:
#ifndef FFUNCTION_H
#define FFUNCTION_H

/** Considering 32-bit input from Ri:
uint8_t r[32] = {1, 0, 1, 1, 0, 1, 1, 0,
                 1, 0, 0, 0, 1, 1, 1, 1,
                 1, 0, 1, 0, 0, 1, 0, 0,
                 1, 1, 0, 1, 1, 1, 0, 0};
**/

const uint8_t sboxTable[8][4][16] = {
        {
        // S-box 1
                14, 4, 13, 1, 2, 15, 11, 8, 
                3, 10, 6, 12, 5, 9, 0, 7,
                0, 15, 7, 4, 14, 2, 13, 1,
                10, 6, 12, 11, 9, 5, 3, 8,
                4, 1, 14, 8, 13, 6, 2, 11, 
                15, 12, 9, 7, 3, 10, 5, 0,
                15, 12, 8, 2, 4, 9, 1, 7, 
                5, 11, 3, 14, 10, 0, 6, 13
        },
        {
        // S-box 2
                15, 1, 8, 14, 6, 11, 3, 4, 
                9, 7, 2, 13, 12, 0, 5, 10,
                3, 13, 4, 7, 15, 2, 8, 14, 
                12, 0, 1, 10, 6, 9, 11, 5,
                0, 14, 7, 11, 10, 4, 13, 1, 
                5, 8, 12, 6, 9, 3, 2, 15,
                13, 8, 10, 1, 3, 15, 4, 2, 
                11, 6, 7, 12, 0, 5, 14, 9
        },
        {
        // S-box 3
                10, 0, 9, 14, 6, 3, 15, 5, 
                1, 13, 12, 7, 11, 4, 2, 8,
                13, 7, 0, 9, 3, 4, 6, 10, 
                2, 8, 5, 14, 12, 11, 15, 1,
                13, 6, 4, 9, 8, 15, 3, 0, 
                11, 1, 2, 12, 5, 10, 14, 7,
                1, 10, 13, 0, 6, 9, 8, 7, 
                4, 15, 14, 3, 11, 5, 2, 12
        },
        {
        // S-box 4
                7, 13, 14, 3, 0, 6, 9, 10, 
                1, 2, 8, 5, 11, 12, 4, 15,
                13, 8, 11, 5, 6, 15, 0, 3,
                4, 7, 2, 12, 1, 10, 14, 9,
                10, 6, 9, 0, 12, 11, 7, 13, 
                15, 1, 3, 14, 5, 2, 8, 4,
                3, 15, 0, 6, 10, 1, 13, 8, 
                9, 4, 5, 11, 12, 7, 2, 14
        },
        {
        // S-box 5
                2, 12, 4, 1, 7, 10, 11, 6, 
                8, 5, 3, 15, 13, 0, 14, 9,
                14, 11, 2, 12, 4, 7, 13, 1, 
                5, 0, 15, 10, 3, 9, 8, 6,
                4, 2, 1, 11, 10, 13, 7, 8, 
                15, 9, 12, 5, 6, 3, 0, 14,
                11, 8, 12, 7, 1, 14, 2, 13, 
                6, 15, 0, 9, 10, 4, 5, 3
        },
        {
        // S-box 6
                12, 1, 10, 15, 9, 2, 6, 8, 
                0, 13, 3, 4, 14, 7, 5, 11,
                10, 15, 4, 2, 7, 12, 9, 5, 
                6, 1, 13, 14, 0, 11, 3, 8,
                9, 14, 15, 5, 2, 8, 12, 3, 
                7, 0, 4, 10, 1, 13, 11, 6,
                4, 3, 2, 12, 9, 5, 15, 10, 
                11, 14, 1, 7, 6, 0, 8, 13
        },
        {
        // S-box 7
                4, 11, 2, 14, 15, 0, 8, 13, 
                3, 12, 9, 7, 5, 10, 6, 1,
                13, 0, 11, 7, 4, 9, 1, 10, 
                14, 3, 5, 12, 2, 15, 8, 6,
                1, 4, 11, 13, 12, 3, 7, 14, 
                10, 15, 6, 8, 0, 5, 9, 2,
                6, 11, 13, 8, 1, 4, 10, 7, 
                9, 5, 0, 15, 14, 2, 3, 12
        },
        {
        // S-box 8
                13, 2, 8, 4, 6, 15, 11, 1, 
                10, 9, 3, 14, 5, 0, 12, 7,
                1, 15, 13, 8, 10, 3, 7, 4, 
                12, 5, 6, 11, 0, 14, 9, 2,
                7, 11, 4, 1, 9, 12, 14, 2, 
                0, 6, 10, 13, 15, 3, 5, 8,
                2, 1, 14, 7, 4, 10, 8, 13,
                15, 12, 9, 0, 3, 5, 6, 11
        }
};

const uint8_t sboxTableHex[256] PROGMEM = {
  // S-box 1
  0xE4, 0xD1, 0x2F, 0xB8, 0x3A, 0x6C, 0x59, 0x07,
  0x0F, 0x74, 0xE2, 0xD1, 0xA6, 0xCB, 0x95, 0x38,
  0x41, 0xE8, 0xD6, 0x2B, 0xFC, 0x97, 0x3A, 0x50,
  0xFC, 0x82, 0x49, 0x17, 0x5B, 0x3E, 0xA0, 0x6D,
  // S-box 2
  0xF1, 0x8E, 0x6B, 0x34, 0x97, 0x2D, 0xC0, 0x5A,
  0x3D, 0x47, 0xF2, 0x8E, 0xC0, 0x1A, 0x69, 0xB5,
  0x0E, 0x7B, 0xA4, 0xD1, 0x58, 0xC6, 0x93, 0x2F,
  0xD8, 0xA1, 0x3F, 0x42, 0xB6, 0x7C, 0x05, 0xE9,
  // S-box 3
  0xA0, 0x9E, 0x63, 0xF5, 0x1D, 0xC7, 0xB4, 0x28,
  0xD7, 0x09, 0x34, 0x6A, 0x28, 0x5E, 0xCB, 0xF1,
  0xD6, 0x49, 0x8F, 0x30, 0xB1, 0x2C, 0x5A, 0xE7,
  0x1A, 0xD0, 0x69, 0x87, 0x4F, 0xE3, 0xB5, 0x2C,
  // S-box 4
  0x7D, 0xE3, 0x06, 0x9A, 0x12, 0x85, 0xBC, 0x4F,
  0xD8, 0xB5, 0x6F, 0x03, 0x47, 0x2C, 0x1A, 0xE9,
  0xA6, 0x90, 0xCB, 0x7D, 0xF1, 0x3E, 0x52, 0x84,
  0x3F, 0x06, 0xA1, 0xD8, 0x94, 0x5B, 0xC7, 0x2E,
  // S-box 5
  0x2C, 0x41, 0x7A, 0xB6, 0x85, 0x3F, 0xD0, 0xE9,
  0xEB, 0x2C, 0x47, 0xD1, 0x50, 0xFA, 0x39, 0x86,
  0x42, 0x1B, 0xAD, 0x78, 0xF9, 0xC5, 0x63, 0x0E,
  0xB8, 0xC7, 0x1E, 0x2D, 0x6F, 0x09, 0xA4, 0x53,
  // S-box 6
  0xC1, 0xAF, 0x92, 0x68, 0x0D, 0x34, 0xE7, 0x5B,
  0xAF, 0x42, 0x7C, 0x95, 0x61, 0xDE, 0x0B, 0x38,
  0x9E, 0xF5, 0x28, 0xC3, 0x70, 0x4A, 0x1D, 0xB6,
  0x43, 0x2C, 0x95, 0xFA, 0xBE, 0x17, 0x60, 0x8D,
  // S-box 7
  0x4B, 0x2E, 0xF0, 0x8D, 0x3C, 0x97, 0x5A, 0x61,
  0xD0, 0xB7, 0x49, 0x1A, 0xE3, 0x5C, 0x2F, 0x86,
  0x14, 0xBD, 0xC3, 0x7E, 0xAF, 0x68, 0x05, 0x92,
  0x6B, 0xD8, 0x14, 0xA7, 0x95, 0x0F, 0xE2, 0x3C,
  // S-box 8 
  0xD2, 0x84, 0x6F, 0xB1, 0xA9, 0x3E, 0x50, 0xC7,
  0x1F, 0xD8, 0xA3, 0x74, 0xC5, 0x6B, 0x0E, 0x92,
  0x7B, 0x41, 0x9C, 0xE2, 0x06, 0xAD, 0xF3, 0x58,
  0x21, 0xE7, 0x4A, 0x8D, 0xFC, 0x90, 0x35, 0x6B
};	

const uint8_t pc1Table[56] = {
        57, 49, 41, 33, 25, 17, 9, 1,
        58, 50, 42, 34, 26, 18, 10, 2,
        59, 51, 43, 35, 27, 19, 11, 3,
        60, 52, 44, 36, 63, 55, 47, 39,
        31, 23, 15, 7, 62, 54, 46, 38,
        30, 22, 14, 6, 61, 53, 45, 37,
        29, 21, 13, 5, 28, 20, 12, 4
};
const uint8_t pc2Table[48] = {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4, 
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40, 
        51, 45, 33, 48, 44, 49, 39, 56, 
        34, 53, 46, 42, 50, 36, 29, 32
};

const uint8_t expansionPermutationTable[48] = {
        32, 1, 2, 3, 4, 5, 4, 5, 
        6, 7, 8, 9, 8, 9, 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17, 
        16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27, 
        28, 29, 28, 29, 30, 31, 32, 1
};

const uint8_t pboxPermutationTable[32] = {
        16, 7, 20, 21, 29, 12, 28, 17, 
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9, 
        19, 13, 30, 6, 22, 11, 4, 25
};

std::string convertDecimalToBinary(int decimal)
{
  std::string binary;
  while(decimal != 0) 
  {
    binary = (decimal % 2 == 0 ? "0" : "1") + binary; 
    decimal = decimal / 2;
  }
  while(binary.length() < 4)
  {
    binary = "0" + binary;
  }
  return binary;
  // For printing, use std::cout or std::string.c_str()
}

int convertBinaryToDecimal(std::string binary)
{
  int decimal = 0, counter = 0;
  int size = binary.length();
  for(int i = size - 1; i >= 0; i--)
  {
    if(binary[i] == '1') 
    {
      decimal += counter * counter;
    }
    counter++;
  }
  return decimal;
}

uint8_t expansionPermutation(uint8_t arr[]) {      
  uint8_t *expandedArray;
  expandedArray = (uint8_t *) malloc(sizeof(expansionPermutationTable) * sizeof(uint8_t));
  for(int i = 0; i < sizeof(expansionPermutationTable); i++)
  {
    expandedArray[i] = arr[expansionPermutationTable[i] - 1];
  }   
  return expandedArray;
}

uint8_t XOR(uint8_t arr[], uint8_t key[]) {
  for(int i = 0; i < 48; i++)
  {
    arr[i] = arr[i] ^ key[i];
  }        
  return arr;      
}        

uint8_t sBoxSubstitution(uint8_t arr[]) {
  // Convert uint8_t array into a string: (using ostringstream from sstream)
  std::ostringstream convert;
  for (int i = 0; i < 48; i++) 
  {
    convert << (int)arr[i];
  }
  std::string expandedString = convert.str();
  std::string substitutedArray = ""; // To store the 32-bit end result (needs conversion back to uint8_t)
  // Iterate through eight 6-bit segments: (48)
  for(int i = 0; i < 8; i++)
  { // Concatenating the extreme 2 bits from a set of 6 to obtain the row:
    std::string row = expandedString.substr(i * 6, 1) + expandedString.substr(i * 6 + 5, 1);
    int convertedRow = convertBinaryToDecimal(row);
    // Concatenating the middle 4 bits from a set of 6 to obtain the column:
    std::string col = expandedString.substr(i * 6 + 1, 1) + expandedString.substr(i * 6 + 2, 1) + expandedString.substr(i * 6 + 3, 1) + expandedString.substr(i * 6 + 4, 1);
    int convertedCol = convertBinaryToDecimal(col);
    int resultantValue = substition_boxes[i][convertedRow][convertedCol];
    substitutedArray += convertDecimalToBinary(resultantValue);  
  }
  uint8_t finalSubstitutedArray[32];
  for (int i = 0; i < 32; i++)
  {
    finalSubstitutedArray[i] = static_cast<uint8_t>(substitutedArray[i] - '0');
    // std::cout << bitset<8>(finalSubstitutedArray[i]) << std::endl;
  }	
  return finalSubstitutedArray;
}

uint8_t pboxPermutation(uint8_t arr[]) {
  uint8_t *permutedArray;
  permutedArray = (uint8_t *) malloc(sizeof(pboxPermutationTable) * sizeof(uint8_t));
  for(int i = 0; i < sizeof(pboxPermutationTable); i++)
  {
    permutedArray[i] = arr[pboxPermutationTable[i] - 1];
  }   
  return permutedArray;
}

/**
uint8_t ffunction(uint8_t r[], uint8_t key[]) {
  // uint8_t expandedArray[32];
  // 32-bit input -> Expansion permutation -> 48-bit output
  // expandedArray = expansionPermutation(r);  
  // 48-bit inputs -> XOR -> 48-bit output
  // xoredArray = XOR(expandedArray, key)
  // 48-bit input -> S-Box -> 32-bit output
  // sBoxSubstitution = sBoxSubstitution(xoredArray)
  // 32-bit input -> P-Box permutation -> 32-bit output  
  // finalArray = pboxPermutation(sBox)
  // return finalArray
}        
**/

#endif
