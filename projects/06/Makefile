CC=gcc

assembler: parser.o translator.o assembler.o symbolTable.o
  $(CC) -o assembler parser.o translator.o assembler.o symbolTable.o

Parser.o: parser.h

Translator.o: translator.h 

Assembler.o: assembler.h

SymbolTable.o: symbolTable.h

clean:
  rm *.o assembler
