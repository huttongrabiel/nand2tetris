#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "symbolTable.h"
#include "assembler.h"
#include "translator.h"
#include <string.h>

struct map predefinedSymbols[23] = {
  {"R0", "@0"}, 
  {"R1", "@1"}, 
  {"R2", "@2"}, 
  {"R3", "@3"}, 
  {"R4", "@4"}, 
  {"R5", "@5"}, 
  {"R6", "@6"}, 
  {"R7", "@7"}, 
  {"R8", "@8"}, 
  {"R9", "@9"}, 
  {"R10", "@10"}, 
  {"R11", "@11"}, 
  {"R12", "@12"}, 
  {"R13", "@13"}, 
  {"R14", "@14"}, 
  {"R15", "@15"}, 
  {"SCREEN", "@16384"}, 
  {"KBD", "@24576"},
  {"SP", "0"}, 
  {"LCL", "1"},
  {"ARG", "2"},
  {"THIS", "3"},
  {"THAT", "4"} 
};

//struct map *programSymbols;

//void *fillSymbolTable(char *line, int programSymbolSize) {
//  // programSymbolSize should be the amount of symbols in the file
//
//  programSymbols = malloc(programSymbolSize * sizeof(struct map));
//  
//  for (int i = 0; i < programSymbolSize; i++) {
//    programSymbols[i].instruction = malloc(strlen(line) * sizeof(char));
//    if (isLabel(line)) {
//      programSymbols[i].binaryInstruction = parseLabel(line);
//    }
//    else if (isVariable(line)) {
//      programSymbols[i].binaryInstruciton = parseAInstruction(line);
//    }
//    programSymbolSize[i].instruction = line;
//    programSymbolSize[i].binaryInstruction = ;
//  }
//}

char line[80];
int getProgramSymbolStructSize(FILE *assemblyCode) {
  // iterate through our input file and count all lines
  // that are labels or variables.

  /* Pseudocode 
    
    Read Through File (get this code from assembler.c;

    int count = 0;
    
    if isLabel():
      count++;
    if isVariable():
      count++;

    return count; 

  */ 
  int programSymbolStructSize = 0;
  int enterKeyHexValue = 0; // UNIX = 0x0a, WINDOWS = 0x0d0a, MAC = 0x0d
  char *trimmedLine;

   while (!feof(assemblyCode) && (fgets(line, 80, assemblyCode) != NULL)) {
  
    enterKeyHexValue = line[0] == 0x0d || line[0] == 0x0a || line[0] == 0x0d0a;
    
    // in this pass over the file, we WANT labels counted 
    if ((line[0] == '/' && line[1] == '/') || enterKeyHexValue) {
      continue;
    }
    else {

      trimmedLine = trimLine(line);
      if (isVariable(trimmedLine) || isLabel(trimmedLine)) {
        printf("%s\n", trimmedLine);
        programSymbolStructSize++;
      }
    }
    line[0] = '\0';
  }
  return programSymbolStructSize;
}

// check if the line is a '(label)'
int isLabel(char *line) {
  int flag = 0;
  if (line[0] == '(') {
    flag = 1;
  }
  return flag;
}

// check if the line is a variable, '@address'
int isVariable(char *line) {
  /*
    check if the line is a variable

    a line is a variable if:
      - it does not start with '('
      - it is not in predefinedSymbols
      - it does not have char 0-9 follow the @
  */

  // 0 = notVariable, 1 = isVariable

  int flag = 0;
 
  // if it starts with an @ but does not follow with a number 
  if (line[0] == '@' && ((int)line[1] > 0x39 || (int)line[1] < 0x30)) {
    flag = 1;
  }

  // checking if it is a predefined symbol
  int sizeOfPreDefSymbols = sizeof(predefinedSymbols) / sizeof (predefinedSymbols[0]);
  for (int i = 0; i < sizeOfPreDefSymbols; i++) {
    if (!strcmp(line, predefinedSymbols[i].instruction)) {
      flag = 0; // if it exists in the table, break 
      break;
    }
  }
  return flag;
}
