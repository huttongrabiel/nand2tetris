#include <stdlib.h>
#include "parser.h"
#include <stdio.h>
#include <string.h>

/*
All we do is parse the inputted file. Split the instructions up
into their respectable pieces. The translator will determine whether
to call the A parser, C (piece) parser, or label. It is easier that way I think.
*/

char *parseAInstruction(char *line) {
  // return the value after the @ sign
  int lenOfLine = strlen(line);
  char *afterAt = malloc(sizeof(char) * lenOfLine-1); // allocate memory for one less then len of line to exclude the @
  sprintf(afterAt, "%s", line + strlen(line) - (lenOfLine-1)); 
  return afterAt;
}

char *parseLabel(char *line) {
  // given (label), returns @label
  int lenOfLine = strlen(line);

  // no idea how long of a name they will give the label so malloc must be
  // multiplied by the (length of the label - 1) to account for removing one
  // parentheses and 'changing' the first to an '@'.
  char *label;
  label = malloc(sizeof(char) * (lenOfLine));
  label[0] = '@';
  label[lenOfLine-1] = '\0';

  for (int j = 1; j < lenOfLine-1; j++) {
    label[j] = line[j];
  }
  return label;
}

char *dest(char *line) {
  // return chars before '=', or null if '=' not in string
  char *destRes;
  destRes = malloc(3 * sizeof(char)); // dest needs three chars max
  int equalFlag = 0; // check for equal sign
  
  // check entire string for equal sign  
  for (int j = 0; j < strlen(line); j++) {
    if (line[j] == '=') {
      equalFlag = 1;
    }
  }
  
  // write destres as if there is an equal sign, this will go to end of line
  // if there is not an equal sign
  for (int i = 0; i < strlen(line); i++) {

    // if i == 3, break before we go beyond destRes allocated memory
    if (line[i] != '=' && i != 3) {
      destRes[i] = line[i];
    }
    else {
      break;
    }

  }

  // if there is no equal sign there is no destination which means we don't store. set dest to "null" -> "000"
  if (equalFlag) {
    return destRes;
  }
  else {
    free(destRes);
    char *nullVal = "null";
    return nullVal;
  }
}

char *jump(char *line) {
  // return chars after ';' to end of line
  char *jumpRes;
  jumpRes = malloc(3 * sizeof(char)); // jump is max three characters
  int semicolon = 0; 

  // if we dont check for a semicolon and the c instruction has no
  // jump value, the program hangs in an endless loop

  int flag = 0; // sets to 1 if ';' is present in string
  for (int j = 0; j < strlen(line); j++) {
    if (line[j] == ';') {
      flag = 1;
    }
  }
  
  int index = 0; // separate index for jumpRes
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
    return jumpRes;
  }
  
  char *nullVal = "null";
  return nullVal;
}

char *comp(char *line) {
  // return computation characters
  char *compRes;
  compRes = malloc(3 * sizeof(char)); // comp is max three characters

  int flag = 0; // if we encounter the '=' we dont want line 141 to execute anymore
  int index = 0; // separate index for charRes
  int equalSign = 0; // flag to check if there is an equal sign

  for (int j = 0; j < strlen(line); j++) {
    if (line[j] == '=') {
      equalSign = 1;
    }
  }
  
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] != '=' && !flag && equalSign) {
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
