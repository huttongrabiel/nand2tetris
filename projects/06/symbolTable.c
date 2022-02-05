#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "symbolTable.h"
#include "assembler.h"
#include "translator.h"
#include <string.h>

struct map predefinedSymbols[23] = {
  {"@R0", "@0"}, 
  {"@R1", "@1"}, 
  {"@R2", "@2"}, 
  {"@R3", "@3"}, 
  {"@R4", "@4"}, 
  {"@R5", "@5"}, 
  {"@R6", "@6"}, 
  {"@R7", "@7"}, 
  {"@R8", "@8"}, 
  {"@R9", "@9"}, 
  {"@R10", "@10"}, 
  {"@R11", "@11"}, 
  {"@R12", "@12"}, 
  {"@R13", "@13"}, 
  {"@R14", "@14"}, 
  {"@R15", "@15"}, 
  {"@SCREEN", "@16384"}, 
  {"@KBD", "@24576"},
  {"SP", "0"}, 
  {"LCL", "1"},
  {"ARG", "2"},
  {"THIS", "3"},
  {"THAT", "4"} 
};

struct map *programSymbols;

// global variables
char **knownVariables;
int *symbolIndex = NULL;
int *labelIndexes;
int labelCount = 0;
int variableCount = 0;
int memoryMultiplier = 1;

int getProgramSymbolStructSize(FILE *assemblyCode) {
  // iterate through our input file and count all lines
  // that are labels or variables.
  char line[80];  
  int programCounter = 0;
  int variableCounter = 16;  
  int programSymbolStructSize = 0;
  int enterKeyHexValue = 0; // UNIX = 0x0a, WINDOWS = 0x0d0a, MAC = 0x0d
  char *trimmedLine;
  int intIndex = 0;

//  char **knownVariables = NULL;
  knownVariables = malloc(128 * sizeof(*knownVariables));
  symbolIndex = malloc(128 * sizeof(int));

  int extraSpaceMultiple = 2;

  int variableCount = 0;
  int duplicateFlag = 0;

  while (!feof(assemblyCode) && (fgets(line, 80, assemblyCode) != NULL)) {
  
    enterKeyHexValue = line[0] == 0x0d || line[0] == 0x0a || line[0] == 0x0d0a;
    
    // in this pass over the file, we WANT labels counted 
    if ((line[0] == '/' && line[1] == '/') || enterKeyHexValue) {
      continue;
    }
    else {
      
      programCounter++;

      trimmedLine = trimLine(line);
      if (isVariable(trimmedLine) || isLabel(trimmedLine)) {

        if (!isPredefined(trimmedLine)) {
          if (isLabel(trimmedLine)) {
            trimmedLine = parseLabel(trimmedLine);
            knownVariables[variableCount] = trimmedLine;
          }
          else {
            knownVariables[variableCount] = trimmedLine;
          }
          
          programSymbolStructSize++;
          variableCount++;
           
          // check if trimmedLine is a duplicate
          for (int i = 0; i < variableCount; i++) {
            for (int j = 0; j < variableCount; j++) {
              if (strcmp(knownVariables[j], knownVariables[i]) == 0 && i != j) {
                duplicateFlag = 1;
              }
            }
          }

          if (duplicateFlag) {
            variableCount--;
            programSymbolStructSize--;
          }
          else {
            if (isLabel(trimLine(line))) {
              printf("Program Counter Plus One = %d\n", programCounter + 1);
              symbolIndex[intIndex] = programCounter + 1;
            }
            else if (isVariable(trimmedLine)) {
              printf("Variable Counter = %d\n", variableCounter);
              symbolIndex[intIndex] = variableCounter;
              variableCounter++;
            }
            printf("Int Index = %d\n", intIndex);
            intIndex++;
          }

          if (variableCount == 128) {
            knownVariables = realloc(knownVariables, extraSpaceMultiple * 128  * sizeof(*knownVariables));
            symbolIndex = realloc(symbolIndex, extraSpaceMultiple * 128 * sizeof(int));
            extraSpaceMultiple++;
          }

        }
      }
    }
    line[0] = '\0';
    duplicateFlag = 0;
  }
//  free(knownVariables);
  return programSymbolStructSize;
}

void addVariables(FILE *assemblyCode) {
  char line[80];
  int variableAddress = 16;
  int index = labelCount;
  char *trimmedLine;
  int enterKeyHexValue = 0;

  while (!feof(assemblyCode) && (fgets(line, 80, assemblyCode) != NULL)) {

    enterKeyHexValue = line[0] == 0x0d || line[0] == 0x0a || line[0] == 0x0d0a;
    if ((line[0] == '/' && line[1] == '/') || enterKeyHexValue) {
      continue;
    }
    else {
      trimmedLine = trimLine(line);
      
      int symbolCount = labelCount + variableCount;

      if (isVariable(trimmedLine) && !isDefined(trimmedLine, programSymbols, symbolCount)) {
        programSymbols[index].instruction = trimmedLine;
        char *variableAddressAsChar = convertIntToChar(variableAddress);
        programSymbols[index].binaryInstruction = variableAddressAsChar;
        variableAddress++;
        index++;
        variableCount++;
      }

      if (index == 128 * memoryMultiplier) {
        memoryMultiplier++;
        programSymbols = realloc(programSymbols, 128 * memoryMultiplier * sizeof(char));
      }
    }
  }
}

void addLabels(FILE *assemblyCode) {
  
  char line[80];
  int programCounter = 1;
  int index = 0;
  char *trimmedLine;
  int enterKeyHexValue = 0;

  programSymbols = malloc(128 * sizeof(struct map));
  labelIndexes = malloc(128 * sizeof(int));

  while (!feof(assemblyCode) && (fgets(line, 80, assemblyCode) != NULL)) {

    enterKeyHexValue = line[0] == 0x0d || line[0] == 0x0a || line[0] == 0x0d0a;

    if ((line[0] == '/' && line[1] == '/') || enterKeyHexValue) {
      continue;
    }
    else {
      trimmedLine = trimLine(line);
      programCounter++;

      if (isLabel(trimmedLine)) {
        programSymbols[index].instruction = parseLabel(trimmedLine);
        char *programCounterAsChar = convertIntToChar(programCounter);
        programSymbols[index].binaryInstruction = programCounterAsChar;
        index++; 
        labelCount++;
      }

      if (index == 128 * memoryMultiplier) {
        memoryMultiplier++;
        programSymbols = realloc(programSymbols, 128 * memoryMultiplier * sizeof(struct map));
      }
    }
  }
}

int isDefined(char *line, struct map *mapArray, int arraySize) {
  int flag = 0;
  for (int i = 0; i < arraySize; i++) {
    if (!strcmp(line, mapArray[i].instruction)) {
      flag = 1;
    }
  }
  return flag;
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
      flag = 0;
      break;
    }
  }
  return flag;
}

int isPredefined(char *line) {
  int flag = 0;
  int sizeOfPredefinedSymbols = sizeof(predefinedSymbols) / sizeof(predefinedSymbols[0]);
  for (int i = 0; i < sizeOfPredefinedSymbols; i++) {
    if (strcmp(line, predefinedSymbols[i].instruction) == 0) {
      flag = 1;
    }
  }
  return flag;
}

// convert integer to string (65 -> "65")
char *convertIntToChar(int val) {
  int size = 0;
  int valCopy = val;
  while (valCopy > 0) {
    valCopy /= 10;
    size++;
  }
  
  char *charInt = malloc(size * sizeof(char));
  int index = size-1;

  while (val > 0) {
    charInt[index] = (val % 10) + '0';
    val /= 10;
    index--;
  }
  return charInt;
}
