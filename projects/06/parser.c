#include <stdlib.h>
#include "parser.h"
#include <stdio.h>
#include <string.h>

/*
All we do is parse the inputted file. Split the instructions up
into their respectable pieces.
*/

int main(void) {
  char *line = "@monkey";
  char *val = instructionSelect(line);
  printf("%s\n", val);
  free(val); // deallocating memory in function

  char *cInstruction = "ADM=M+1;JGT";
  char *cInVal = instructionSelect(cInstruction);
  printf("%s\n", cInVal);
  free(cInVal);

  char *Label = "(loop)";
  char *userLabel = instructionSelect(Label);
  printf("%s\n", userLabel);
  free(userLabel);

  return(0);
}

char *parseAInstruction(char *line) {
  // return the value after the @ sign
  int lenOfLine = strlen(line);
  char *afterAt = malloc(sizeof(char) * lenOfLine-1); // allocate memory for one less then len of line to exclude the @
  sprintf(afterAt, "%s", line + strlen(line) - (lenOfLine-1)); 
  return afterAt;
}

char *parseCInstruction(char *line) {
  // returns dest, comp, and jmp strings with a space between each 

  int lenOfLine = strlen(line);
  char *cInstruction;
  cInstruction = malloc(9 * sizeof(char)); // give it three chararacter allocation

  for (int i = 0; i < lenOfLine; i++) {
    if (line[i] == '=' || line[i] == ';') {
      cInstruction[i] = ' ';
    }
    else {
      cInstruction[i] = line[i];
    }
  }

  return cInstruction;
}

char *parseLabel(char *line) {
  // return value of a label: (label)
  int lenOfLine = strlen(line);

  // no idea how long of a name they will give the label so malloc must be
  // multiplied by the (length of the label - 2) to account for the parentheses
  char *label;
  label = malloc(sizeof(char) * (lenOfLine-2));
  
  int labelIndex = 0; // have to track the index separately
  for (int j = 1; j < lenOfLine-1; j++) {
    label[labelIndex] = line[j];
    labelIndex++;
  }
  
  return label;
}

char *instructionSelect(char *line) {
  // Calls either parseA or parseC depending on value of the line's first char 
  if (line[0] == '@') {
    parseAInstruction(line);
  }
  else if (line[0] != '('){
    parseCInstruction(line);
  }
  else {
    parseLabel(line);
  }
}
