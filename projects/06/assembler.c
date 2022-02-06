#include <stdio.h>
#include <stdlib.h>
#include "translator.h"
#include "parser.h"
#include <string.h>
#include "assembler.h"
#include "symbolTable.h"

int main(int argc, char *argv[]) {
  // read the file line by line, skip to next line if we come across "//", 
  // skip to next line if white space, otherwise read first char of line and
  // pass to parseAinstruction or parseCInstruction, add output the instruction
  // to the binary file. Clear instruction string, start over again
  
  FILE *dotHack; // file to write to
  FILE *assemblyCode; // file to read from
  char line[80]; // give it 80 chars for standard line length
  char *trimmedLine;
  
  // make sure file is given to assembler
  if (argc != 2) {
    fprintf(stderr, "\nERROR: enter command line parameter\n");
    exit(1);
  }
  
  // make sure file exists and can be opened
  if ((assemblyCode = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "\nERROR: file %s is invalid.\n", argv[1]);
    exit(1);
  }

  // create output file
  dotHack = fopen("out.hack", "w+");

  // filling in symbol table
  addLabels(assemblyCode);
  rewind(assemblyCode);
  addVariables(assemblyCode);
  rewind(assemblyCode);

  int enterKeyHexValue = 0; // UNIX = 0x0a, WINDOWS = 0x0d0a, MAC = 0x0d

  // while not at EOF and fgets() does not return NULL, print line.
  // clear line and repeat. if statement checks for comments, "//", 
  // and carriage return / line feed (newline) 
  while (!feof(assemblyCode) && (fgets(line, 80, assemblyCode) != NULL)) {
  
    enterKeyHexValue = line[0] == 0x0d || line[0] == 0x0a || line[0] == 0x0d0a;
    
    // if comment, newLine, or label, continue
    if ((line[0] == '/' && line[1] == '/') || enterKeyHexValue || line[0] == '(') {
      continue;
    }
    else {
      
      trimmedLine = trimLine(line);

      if (trimmedLine[0] == '@') {
        char *AInstruction;
        int symbolCount = labelCount + variableCount;

        if (isDefined(trimmedLine, programSymbols, symbolCount)) {
          int indexInProgramSymbols = indexOf(trimmedLine, programSymbols, symbolCount);
          AInstruction = translateAInstruction(programSymbols[indexInProgramSymbols].binaryInstruction);
        }
        else if (isPredefined(trimmedLine)) {
          int indexInPredefinedSymbols = indexOf(trimmedLine, predefinedSymbols, 23);
          AInstruction = translateAInstruction(predefinedSymbols[indexInPredefinedSymbols].binaryInstruction);
        }
        else {
          AInstruction = translateAInstruction(trimmedLine);
        }
        fputs(AInstruction, dotHack);
        fprintf(dotHack, "%c", '\n');
        free(AInstruction);
      }
      else {
        char *CInstruction;
        CInstruction = translateCInstruction(trimmedLine);
        fputs(CInstruction, dotHack);
        fprintf(dotHack, "%c", '\n');
        free(CInstruction);
      }
      
      free(trimmedLine);
      trimmedLine = NULL;
      line[0] = '\0';
    }
  }

  fclose(assemblyCode);
  fclose(dotHack);

  return 0;
}

// trim line of blank characters that fgets adds due to large buffer size
// trimline needs a rewrite because when we have loops we have blank chars
// to the left and the right of the string that we want. meaning we have to check
// if char[0] == ' ' and if it does we need to increase our index until line[i]
// equals '@'
char *trimLine(char *line) { 
  int count = 0;
  int countBlankChars = 0;
  int commentStartIndex = getCommentIndex(line);

  for (int j = 0; j < commentStartIndex; j++) {
    if (line[j] == 0x20 || line[j] == 0x0d || line[j] == 0x0a || line[j] == 0x0d0a) {
      count++;
    }
    if (line[j] == 0x20) {
      countBlankChars++;
    }
  }

  // setting our starting index postition
  int startIndex = 0;
  for (int i = 0; i < strlen(line); i++) {
    if ((int)line[i] != 0x20) {
      break;
    }
    if ((int)line[i] == 0x20) {
      startIndex++;
    }
  }
  
  int trimmedLineLen = commentStartIndex - count; // total amount of chars - blank chars

  char *trimmedLine = NULL;
  trimmedLine = malloc(trimmedLineLen+1 * sizeof(char));

  trimmedLine[trimmedLineLen] = '\0'; 

  int lineIndex = 0;
  for (int i = startIndex; i < trimmedLineLen+startIndex; i++) {
    trimmedLine[lineIndex] = line[i];
    lineIndex++;
  }

  return trimmedLine;
}

int indexOf(char *line, struct map *mapArr, int mapArrSize) {
  int index = 0;
  for (int i = 0; i < mapArrSize; i++) {
    if (!strcmp(mapArr[i].instruction, line)) {
      index = i;
      break;
    }
  }
  return index;
}

int getCommentIndex(char *line) {
  int commentStartIndex = strlen(line);
  for (int i = 0; i < strlen(line)-1; i++) {
    if (line[i] == '/' && line[i+1] == '/') {
      commentStartIndex = i;
    }
  }
  return commentStartIndex;
}
