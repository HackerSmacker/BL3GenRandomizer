#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Spawns.h"
#include <bl3mod.h>

/* libbl3mod + randomizer */
/* In theory, this should work perfectly. */

FILE* outFile;

int main(int argc, char** argv) {
	char replacement[512];
	int i;
	int j;
	int k;
	char* line;
	char* filename = "";
	int choice;
	srand(time(NULL));
	if(argc < 2) {
		filename = "spawn_randomizer.txt";
	}
	else {
		filename = argv[1];
	}
	printf("MKSPAWNRAND Spawn randomizer generator. Use DLC = yes; output file = %s\n", filename);
	outFile = fopen(filename, "w");
	if(!outFile) {
		printf("MKSPAWNRAND Failed to open output file\n");
		exit(1);
	}
	fprintf(outFile, fileHeader);
	for(i = 0; i < listNumSpawnOptions - 1; i++) {
		choice = rand() % (listNumBPChars - 1);
		memset(replacement, 0x00, 512);
		sprintf(replacement, "BlueprintGeneratedClass'\"%s\"'", end_object_c(bpChars[choice]));
		line = regular_hotfix(MOD_TYPE_EARLYLEVEL, extract_object(spawnOptions[i]), "Options.Options[0].Factory.Object..AIActorClass", replacement, 0);
		fwrite(line, sizeof(char), strlen(line), outFile);
		printf("%s is now a %s\n", spawnOptions[i], bpChars[choice]);
	}
	fprintf(outFile, fileFooter);
	return 0;
}
