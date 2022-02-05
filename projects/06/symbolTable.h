#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

extern char **knownVariables;
extern int labelCount;
extern int *labelIndexes;
extern struct map *programSymbols;

int getProgramSymbolStructSize(FILE *);
int isLabel(char *);
int isVariable(char *);
int isPredefined(char *);
char *convertIntToChar(int);
void addLabels(FILE *);
void addVariables(FILE *);
int isDefined(char *, char **, int);

#endif
