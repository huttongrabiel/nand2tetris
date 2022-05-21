#ifndef ASSEMBLER
#define ASSEMBLER

char *trimLine(char *);
int indexOf(char *, struct map *, int);
char *removeComments(char *);
int getCommentIndex(char *);
void freeProgramSymbols();

#endif
