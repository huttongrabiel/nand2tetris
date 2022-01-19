#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "translator.h"
#include "parser.h"

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

int main(void) {
  char *line = "AD=M+1;JGT";
  char *destValue = dest(line);
  char *testResult = linearSearch(destValue, DestOpCodes);
  printf("%s\n", testResult); 
}

char *linearSearch(char *instruction, struct map opCodes[]) {
  // linearSearch is fast enough, there is, at most, 28 options
  char *result;
  result = malloc(strlen(opCodes[0].binaryInstruction) * sizeof(char));

  int arrSize = sizeof(opCodes); 
  for (int i = 0; i < arrSize; i++) {
    if (!strcmp(instruction,opCodes[i].instruction)) { // might roll my own strcmp
      result = opCodes[i].binaryInstruction;
    }
  }
  
  return result;
} 
