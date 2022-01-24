#ifndef TRANSLATOR
#define TRANSLATOR

struct map {
  char *instruction;
  char *binaryInstruction;
};

char *linearSearch(char *, struct map val[], int);
char *translateAInstruction(char *);
char *translateCInstruction(char *);

#endif
