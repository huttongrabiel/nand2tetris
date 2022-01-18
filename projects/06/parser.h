#ifndef PARSER 
#define PARSER 

char *parseAInstruction(char *);
char *parseCInstruction(char *);
char *parseLabel(char*);
char *instructionSelect(char *);
char *dest(char *);
char *jump(char *);
char *comp(char *);

#endif
