#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // read the file line by line, skip to next line if we come across "//", 
  // skip to next line if white space, otherwise read first char of line and
  // pass to parseAinstruction or parseCInstruction, add output the instruction
  // to the binary file. Clear instruction string, start over again

  FILE *assemblyCode;

  if ((assemblyCode = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "\nERROR: file %s is invalid.\n", argv[1]);
    return 0;
  }
  

}
