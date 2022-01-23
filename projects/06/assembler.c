#include <stdio.h>
#include <stdlib.h>
#include "translator.h"

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
      printf("%s", line);
      line[0] = '\0';
    }
  }

  fclose(assemblyCode);

  return 0;
}
