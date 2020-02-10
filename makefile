CFLAGS = -g -O2 -Wall -Werror `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`


FELite: FEMain.o FEFunctions.o 
		gcc -o FELite FEMain.o FEFunctions.o -g -O2 -Wall -Werror `pkg-config --libs MLV`

FEMain.o: FEMain.c FEFunctions.h FEStructures.h
	gcc -o FEMain.o -c FEMain.c -Wall -ansi  

FEFunctions.o: FEFunctions.c FEFunctions.h FEStructures.h
	     gcc -o FEFunctions.o -c FEFunctions.c -Wall -ansi 

#clean:
#	rm -rf $(TARGET)
