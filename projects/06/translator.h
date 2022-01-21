#ifndef TRANSLATOR
#define TRANSLATOR

struct map {
  char *instruction;
  char *binaryInstruction;
};

char *linearSearch(char *, struct map val[], int);
int instructionSelect(char *);
char *translateAInstruction(char *);
char *translateCInstruction(char *);

#endif
