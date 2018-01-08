

FELite: FEMain.o FEFunctions.o
		gcc -o FELite FEMain.o FEFunctions.o

FEMain.o: FEMain.c FEFunctions.h FEStructures.h
	gcc -o FEMain.o -c FEMain.c -Wall -ansi

FEFunctions.o: FEFunctions.c FEFunctions.h FEStructures.h
	     gcc -o FEFunctions.o -c FEFunctions.c -Wall -ansi