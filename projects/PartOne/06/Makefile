CC=gcc
CFLAGS= -g

assembler: parser.o translator.o assembler.o symbolTable.o
	$(CC) -o assembler $(CFLAGS) parser.o translator.o assembler.o symbolTable.o

Parser.o: parser.h 

Translator.o: translator.h  parser.h

Assembler.o: assembler.h translator.h symbolTable.h

SymbolTable.o: assembler.h translator.h parser.h symbolTable.h

clean:
	rm *.o assembler
