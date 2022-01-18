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

  char *cInstruction = "D=M";
  char *cInVal = instructionSelect(cInstruction);
  printf("%s\n", cInVal);

  char *destValue = dest(cInstruction);
  printf("%s\n", destValue); // testing dest function
  
  char *jumpValue = jump(cInstruction);
  printf("%s\n", jumpValue);

  char *compValue = comp(cInstruction);
  printf("%s\n", compValue);

  char *Label = "(loop)";
  char *userLabel = instructionSelect(Label);
  printf("%s\n", userLabel);

  // freeing all allocations
  free(userLabel);
  free(destValue);
  free(jumpValue);
  free(compValue);
  free(cInVal);

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
  cInstruction = malloc(11 * sizeof(char)); // give it eleven chararacter allocation

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

// The following three functions are probably not the best way to go about
// getting each part but it works

char *dest(char *line) {
  // return chars before '=', or null if '=' not in string
  char *destRes;
  destRes = malloc(3 * sizeof(char)); // dest needs three chars max

  for (int i = 0; i < strlen(line); i++) {
    if (line[i] != '=') {
      destRes[i] = line[i];
    }
    else {
      break;
    }
  }
  
  return destRes;
}

char *jump(char *line) {
  // return chars after '=' and before ';', or to end depending on instruction
  char *jumpRes;
  jumpRes = malloc(3 * sizeof(char)); // jump is max three characters
  int semicolon = 0; 

  int flag = 0; // sets to 1 if ';' is present in string
  for (int j = 0; j < strlen(line); j++) {
    if (line[j] == ';') {
      flag = 1;
    }
  }
  
// if we dont check for a semicolon and the c instruction has no
// jump value, the program hangs in an endless loop
  int index = 0;
  if (flag) {

    for (int i = 0; i < strlen(line); i++) {
      // move through the string until the = sign
      if (line[i] != ';' && semicolon == 0) {
        continue;
      }
      
      // go the character past the semicolon
      if (line[i] == ';') {
        semicolon = 1;
        continue;
      }

      // add character to result string until end of line
      if (line[i] != '\0') {
        jumpRes[index] = line[i];
        index++;
      }
      else {
        break;
      }
    }

  }

  return jumpRes;
}

char *comp(char *line) {
  // return chars after =, other wise return "nul"
  char *compRes;
  compRes = malloc(3 * sizeof(char)); // comp is max three characters
  int flag = 0; // if we encounter the '=' we dont want the above if to execute anymore
  int index = 0;
  
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] != '=' && flag == 0) {
      continue;
    }
    
    if (line[i] == '=') {
      flag = 1;
      continue;
    }

    if (line[i] != ';' && line[i] != '\0') {
      compRes[index] = line[i];
      index++;
    }
    else {
      break;
    }
  }

  return compRes;
}
