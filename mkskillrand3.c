#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "Skills.h"



int main(int argc, char** argv) {
	char* filename = "";
	if(argc < 2) {
		filename = "skill_randomizer3.txt";
	}
	else {
		filename = argv[1];
	}
	printf("MKSKILLRAND Skill randomizer generator. Trees = 3; output file = %s\n", filename);
	FILE* outFile;
	outFile = fopen(filename, "w");
	if(!outFile) {
		printf("MKSKILLRAND Failed to open output file\n");
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
	numTrees = 12;
	char* classPath;
	char* classEndWithSlash;
	char* classEnd;
	char* skillPath;
	char* skillEndWithSlash;
	char* skillEnd;
	for(k = 0; k < numTrees; k++) {
		for(i = 1; i < numTiers + 1; i++) {
			for(j = 0; j < numSkills; j++) {
				skillChoice = (rand() % (listNumSkills3));
				classPath = skillTrees[k];
				classEndWithSlash = strrchr(skillTrees[k], '/');
				classEnd = malloc(strlen(classEndWithSlash) - 1);
				strcpy(classEnd, classEndWithSlash + 1);
				skillPath = skills[skillChoice];
				skillEndWithSlash = strrchr(skills[skillChoice], '/');
				skillEnd = malloc(strlen(skillEndWithSlash) - 1);
				strcpy(skillEnd, skillEndWithSlash + 1);
				//printf("%s.%s\n", classPath, classEnd);
				fprintf(outFile, "SparkPatchEntry,(1,1,0,),%s.%s,Tiers.Tiers[%d].Object..Items.Items[%d].Object..ItemFrameName,0,,\n", classPath, classEnd, i, j);
				fprintf(outFile, "SparkPatchEntry,(1,1,0,),%s.%s,Tiers.Tiers[%d].Object..Items.Items[%d].Object..AbilityClass,0,,BlueprintGeneratedClass'\"%s.%s_C\"'\n", classPath, classEnd, i, j, skillEnd, skillEnd);
			}
		}
	}
	fprintf(outFile, "### Thank you for choosing mkskillrand! EOF.\n");
	return 0;
}
