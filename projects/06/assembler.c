#include <stdio.h>
#include <stdlib.h>
#include "translator.h"
#include "parser.h"
#include <string.h>
#include "assembler.h"

int main(int argc, char *argv[]) {
  // read the file line by line, skip to next line if we come across "//", 
  // skip to next line if white space, otherwise read first char of line and
  // pass to parseAinstruction or parseCInstruction, add output the instruction
  // to the binary file. Clear instruction string, start over again
  
  FILE *dotHack; // file to write to
  FILE *assemblyCode; // file to read from
  char line[80]; // give it 80 chars for standard line length
  
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
  
  int enterKeyHexValue; // UNIX = 0a, WINDOWS = 0x0d0a, MAC = 0x0d

  // while not at EOF and fgets() does not return NULL, print line.
  // clear line and repeat. if statement checks for comments, "//", 
  // and white space which are new lines 
  while (!feof(assemblyCode) && (fgets(line, 80, assemblyCode) != NULL)) {
  
    enterKeyHexValue = line[0] == 0x0d || line[0] == 0x0a || line[0] == 0x0d0a;

    if ((line[0] == '/' && line[1] == '/') || enterKeyHexValue) {
      continue;
    }
    else {

      char *trimmedLine = trimLine(line);

      if (trimmedLine[0] == '@') {
        char *storVal;
        storVal = translateAInstruction(trimmedLine);
        printf("%s\n", storVal);
      }
      else {
        char *storVal2;
        storVal2 = translateCInstruction(trimmedLine);
        printf("%s\n", storVal2);
      }

      line[0] = '\0';
      free(trimmedLine);
    }
  }

  fclose(assemblyCode);

  return 0;
}

// trim line of blank characters that fgets adds due to large buffer size
char *trimLine(char *line) { 
  int count = 0;
  for (int j = 0; j < strlen(line); j++) {
    if (line[j] == ' ') {
      count++;
    }
  }

  int trimmedLineLen = strlen(line) - count; // total amount of chars - blank chars

  char *trimmedLine;
  trimmedLine = malloc(trimmedLineLen * sizeof(char));

  for (int i = 0; i < trimmedLineLen; i++) {
    if (line[i] == ' ') {
      break;
    }
    trimmedLine[i] = line[i];
  }
  return trimmedLine;
}
