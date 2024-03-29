#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "translator.h"
#include "parser.h"
#include "assembler.h"

// struct function defined in translator.h

struct map DestOpCodes[8] = { 
  {"null", "000"},
  {"M", "001"},
  {"D", "010"},
  {"MD", "011"},
  {"A", "100"},
  {"AM", "101"},
  {"AD", "110"},
  {"AMD", "111"}
};

struct map JumpOpCodes[8] = { 
  {"null", "000"}, 
  {"JGT", "001"},
  {"JEQ", "010"},
  {"JGE", "011"},
  {"JLT", "100"},
  {"JNE", "101"},
  {"JLE", "110"},
  {"JMP", "111"}
};

struct map CompOpCodes[28] = { 
  {"0", "0101010"},
  {"1", "0111111"},
  {"-1", "0111010"},
  {"D", "0001100"}, 
  {"A", "0110000"},
  {"!D", "0001101"},
  {"!A", "0110011"},
  {"-D", "0001111"},
  {"-A", "0110011"},
  {"D+1", "0011111"},
  {"A+1", "0110111"},
  {"D-1", "0001110"},
  {"A-1", "0110010"},
  {"D+A", "0000010"},
  {"D-A", "0010011"},
  {"A-D", "0000111"},
  {"D&A", "0000000"},
  {"D|A", "0010101"},
  {"M", "1110000"},
  {"!M", "1110001"},
  {"-M", "1110011"},
  {"M+1", "1110111"},
  {"M-1", "1110010"},
  {"D+M", "1000010"},
  {"D-M", "1010011"},
  {"M-D", "1000111"},
  {"D&M", "1000000"},
  {"D|M", "1010101"}
};

// returns binary instruction of given assembly instruction
char *linearSearch(char *instruction, struct map opCodes[], int arraySize) {
  // linearSearch is fast enough, there is, at most, 28 options
  char *result = NULL;
  result = malloc(strlen(opCodes[0].binaryInstruction) * sizeof(char));

  for (int i = 0; i < arraySize; i++) {
    if (!strcmp(instruction,opCodes[i].instruction)) { // might roll my own strcmp
      result = opCodes[i].binaryInstruction;
    }
  }
  
  return result;
}

char *translateAInstruction(char *line) {
  // convert the decimal value after the @ sign to binary
  // as of rn, assume line is an a instruction even though that functionality
  // has not been implemented yet
  // This will eventually have to do a lookup in the symbol table if it is a not a
  // number that follows the @. 

  int lenOfLine = strlen(line);

  // converts char in a instruction to int
  int decimalValue = 0;
  int tensPlaceMultiplier = 1;
  int charToDecimal = 0;
  int jIndex = strlen(line) - 2;

  for (int i = 1; i < lenOfLine; i++) {
    charToDecimal += line[i] - '0'; // char to int conversion. just subtract '0'
    if (charToDecimal == 79) {
      printf("Line = %s\n", line);
      printf("i = %d\n", i);
    }
    for (int j = jIndex; j > 0; j--) {
      tensPlaceMultiplier *= 10;
    }
    decimalValue += (tensPlaceMultiplier * charToDecimal);
    tensPlaceMultiplier = 1;
    jIndex--;
    charToDecimal = 0;
  }

  // converts int into binary
  int bitmask = 0x8000; // 1000000000000000 in binary (16 bits)
  char *binaryResult;
  binaryResult = malloc(17 * sizeof(char));
  binaryResult[16] = '\0';

  int index = 0;
  while (bitmask > 0) {
    binaryResult[index] = bitmask & decimalValue ? '1' : '0';
    bitmask = bitmask >> 1;
    index++;
  }

  return binaryResult;
}

char *translateCInstruction(char *line) {
  // given a c instruction convert it to it's machine language equivalent
  // 16 bit value
  // starts with 111
  // then comp, dest, jump

  char *cInstruction = NULL;
  cInstruction = malloc(17 * sizeof(char));
  cInstruction[16] = '\0';
  

  // starts with 111
  for (int i = 0; i < 3; i++) {
    cInstruction[i] = '1';
  }

  char *compValue = comp(line);
  char *compBinaryInstruction = linearSearch(compValue, CompOpCodes, 28);

  // placing the comp instruction into its position in the c instruction
  int compIndex = 0;
  for (int i = 3; i < 10; i++) {
    cInstruction[i] = compBinaryInstruction[compIndex];
    compIndex++;
  }

  char *destValue = dest(line);
  char *destBinaryInstruction = linearSearch(destValue, DestOpCodes, 8);

  // placing the dest instruction into its position in the c instruction
  int destIndex = 0;
  for (int i = 10; i < 13; i++) {
    cInstruction[i] = destBinaryInstruction[destIndex];
    destIndex++;
  }

  char *jumpValue = jump(line);
  char *jumpBinaryInstruction = linearSearch(jumpValue, JumpOpCodes, 8);

  // placing the jump instruction into its position in the c instruction
  int jumpIndex = 0;
  for (int i = 13; i < 16; i++) {
    cInstruction[i] = jumpBinaryInstruction[jumpIndex];
    jumpIndex++;
  }

//  free(compValue);
//  free(compBinaryInstruction);
//  free(destValue);
//  free(destBinaryInstruction);
//  free(jumpValue);
//  free(jumpBinaryInstruction);

  return cInstruction;
}
