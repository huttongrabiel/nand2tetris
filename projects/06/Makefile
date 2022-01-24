CC=gcc

assembler: parser.o translator.o assembler.o 
	$(CC) -o assembler parser.o translator.o assembler.o 

Parser.o: parser.h 

Translator.o: translator.h  parser.h

Assembler.o: assembler.h translator.h

clean:
	rm *.o assembler
