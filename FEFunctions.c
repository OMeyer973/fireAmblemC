#include <stdio.h>
#include <stdlib.h>
#include "FEStructures.h"
#include "FEFunctions.h"

int afficheMonde (Monde md) {
	int x = 0;
	int y = 0;
	for (x=0; x<HAUT; x++) {
		printf("-------------------------------------------------------------------------------------------\n");
		for (y=0; y< LARG; y++) {
			if (md.plateau[x][y] == NULL) {
				printf("|XXXX");	
			}
			else {
				printf("|    ");
			}
		}
		printf("|\n");
	}
	printf("-------------------------------------------------------------------------------------------\n");
	return 1;
}