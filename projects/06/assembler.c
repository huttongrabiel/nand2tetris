#include <stdio.h>
#include <stdlib.h>
#include "translator.h"

int main(int argc, char *argv[]) {
  // read the file line by line, skip to next line if we come across "//", 
  // skip to next line if white space, otherwise read first char of line and
  // pass to parseAinstruction or parseCInstruction, add output the instruction
  // to the binary file. Clear instruction string, start over again

  FILE *assemblyCode;
  
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
  
  // read file line by line. clear line after converting to binary
  // instruction. repeat



  fclose(assemblyCode);

  return 0;
}
