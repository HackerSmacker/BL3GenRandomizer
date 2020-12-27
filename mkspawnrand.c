#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "Spawns.h"



int main(int argc, char** argv) {
	char* filename = "";
	if(argc < 2) {
		filename = "spawn_randomizer.txt";
	}
	else {
		filename = argv[1];
	}
	printf("MKSPAWNRAND Skill randomizer generator. Use DLC = yes; output file = %s\n", filename);
	FILE* outFile;
	outFile = fopen(filename, "w");
	if(!outFile) {
		printf("MKSPAWNRAND Failed to open output file\n");
		exit(1);
	}

	fprintf(outFile, fileHeader);
	int i;
	int j;
	int k;
	int replaceChoice;
	char* replacerPath;
	char* replacerEndWithSlash;
	char* replacerEnd;
	char* replacerEndWithC;
	char* currentPath;
	char* currentEndWithSlash;
	char* currentEnd;
	for(i = 0; i < listNumSpawnOptions - 1; i++) {
		replaceChoice = (rand() % (listNumBPChars - 1)); 
		replacerPath = bpChars[replaceChoice];
		replacerEndWithSlash = strrchr(replacerPath, '/');
		replacerEnd = malloc(strlen(replacerEndWithSlash) - 1);
		strcpy(replacerEnd, replacerEndWithSlash + 1);
		replacerEndWithC = malloc(strlen(replacerEnd) + 3);
		strcpy(replacerEndWithC, replacerEnd);
		strcat(replacerEndWithC, "_C");
		
		currentPath = spawnOptions[i];
		currentEndWithSlash = strrchr(currentPath, '/');
		currentEnd = malloc(strlen(currentEndWithSlash) - 1);
		strcpy(currentEnd, currentEndWithSlash + 1);
		//printf("%s.%s is now a %s.%s\n", currentPath, currentEnd, replacerPath, replacerEnd);
		fprintf(outFile, "SparkEarlyLevelPatchEntry,(1,1,0,MatchAll),%s.%s,Options.Options[0].Factory.Object..AIActorClass,0,,BlueprintGeneratedClass'\"%s.%s\"'\n", currentPath, currentEnd, replacerPath, replacerEndWithC);
	}
	fprintf(outFile, fileFooter);
	return 0;
}
