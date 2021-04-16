#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Spawns.h"
#include <bl3mod.h>

/* libbl3mod + randomizer */
/* In theory, this should work perfectly. */

int main(int argc, char** argv) {
	char replacement[512];
	int i;
	int j;
	int k;
	char* line;
	srand(time(NULL));
	char* filename = "";
	if(argc < 2) {
		filename = "spawn_randomizer.txt";
	}
	else {
		filename = argv[1];
	}
	printf("MKSPAWNRAND Spawn randomizer generator. Use DLC = yes; output file = %s\n", filename);
	FILE* outFile;
	outFile = fopen(filename, "w");
	if(!outFile) {
		printf("MKSPAWNRAND Failed to open output file\n");
		exit(1);
	}
	fprintf(outFile, fileHeader);
	for(i = 0; i < listNumSpawnOptions - 1; i++) {
		bzero(replacement, 512);
		sprintf(replacement, "BlueprintGeneratedClass'\"%s\"'", end_object_c(bpChars[rand() % (listNumBPChars - 1)]));
		line = regular_hotfix(MOD_TYPE_EARLYLEVEL, extract_object(spawnOptions[i]), "Options.Options[0].Factory.Object..AIActorClass", replacement, 0);
		fwrite(line, sizeof(char), strlen(line), outFile);
	}
	fprintf(outFile, fileFooter);
	return 0;
}
