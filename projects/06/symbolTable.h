#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

extern char **knownVariables;
extern int labelCount;
extern int variableCount;
extern int *labelIndexes;
extern struct map *programSymbols;
extern struct map predefinedSymbols[];

int isLabel(char *);
int isVariable(char *);
int isPredefined(char *);
char *convertIntToChar(int);
void addLabels(FILE *);
void addVariables(FILE *);
int isDefined(char *, struct map *, int);

#endif
