#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "Skills.h"



int main(int argc, char** argv) {
	if(argc < 2) {
		printf("MKSKILLBLANK Usage: \"mkskillblank out.txt\"\n");
		exit(1);
	}
	printf("MKSKILLBLANK Skill randomizer generator, zeros out the skill names. Trees = 4; output file = %s\n", argv[1]);
	FILE* outFile;
	outFile = fopen(argv[1], "w");
	if(!outFile) {
		printf("MKSKILLBLANK Failed to open output file\n");
		exit(1);
	}

	fprintf(outFile, fileHeader);
	// I know somebody's gonna ask why I define the vars and init them
	// on separate lines... it's called C89
	int i;
	int j;
	int k;
	int skillChoice;
	int numTiers;
	numTiers = 6;
	int numSkills;
	numSkills = 3;
	int numTrees;
	numTrees = 16;
	char* classPath;
	char* classEndWithSlash;
	char* classEnd;
	for(k = 0; k < numTrees; k++) {
		for(i = 1; i < numTiers + 1; i++) {
			for(j = 0; j < numSkills; j++) {
				classPath = skillTrees[k];
				classEndWithSlash = strrchr(skillTrees[k], '/');
				classEnd = malloc(strlen(classEndWithSlash) - 1);
				strcpy(classEnd, classEndWithSlash + 1);
				//printf("%s.%s\n", classPath, classEnd);
				fprintf(outFile, "SparkPatchEntry,(1,1,0,),%s.%s,Tiers.Tiers[%d].Object..Items.Items[%d].Object..ItemFrameName,0,,\n", classPath, classEnd, i, j);
			}
		}
	}
	fprintf(outFile, fileFooter);
	return 0;
}
