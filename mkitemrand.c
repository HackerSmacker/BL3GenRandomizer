#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "Items.h"



int main(int argc, char** argv) {
	char* filename = "";
	if(argc < 2) {
		filename = "item_randomizer.txt";
	}
	else {
		filename = argv[1];
	}
	printf("MKITEMRAND Item randomizer generator. Use DLC = yes; output file = %s\n", filename);
	FILE* outFile;
	outFile = fopen(filename, "w");
	if(!outFile) {
		printf("MKITEMRAND Failed to open output file\n");
		exit(1);
	}

	fprintf(outFile, fileHeader);
	int i;
	int j;
	int k;
	int replaceChoice;
	for(i = 0; i < listNumBalanceWeapon - 1; i++) {

	}
	fprintf(outFile, fileFooter);
	return 0;
}
