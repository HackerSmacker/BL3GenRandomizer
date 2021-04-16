#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Items.h"

FILE* outFile;


int main(int argc, char** argv) {
	int i;
	int j;
	int k;
	int replaceChoice;
	char* filename = "";
	srand(time(NULL));
	if(argc < 2) {
		filename = "item_randomizer.txt";
	}
	else {
		filename = argv[1];
	}
	printf("MKITEMRAND Item randomizer generator. Use DLC = yes; output file = %s\n", filename);
	outFile = fopen(filename, "w");
	if(!outFile) {
		printf("MKITEMRAND Failed to open output file\n");
		exit(1);
	}
	fprintf(outFile, fileHeader);
	for(i = 0; i < listNumBalanceWeapon - 1; i++) {
		printf(".");
	}
	fprintf(outFile, fileFooter);
	return 0;
}
