#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "Skills.h"



int main(int argc, char** argv) {
	if(argc < 2) {
		printf("MKSKILLRAND Usage: \"mkskillrand3 out.txt\"\n");
		exit(1);
	}
	printf("MKSKILLRAND Skill randomizer generator. Trees = 4; output file = %s\n", argv[1]);
	FILE* outFile;
	outFile = fopen(argv[1], "w");
	if(!outFile) {
		printf("MKSKILLRAND Failed to open output file\n");
		exit(1);
	}

	fprintf(outFile, fileHeader);
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
	for(k = 0; k < numTrees; k++) {
		for(i = 1; i < numTiers + 1; i++) {
			for(j = 0; j < numSkills; j++) {
				skillChoice = (rand() % (listNumSkills4));
				fprintf(outFile, "SparkPatchEntry,(1,1,0,),%s,Tiers.Tiers[%d].Object..Items.Items[%d].Object..ItemFrameName,0,,\n", skillTrees[k], i, j);
				fprintf(outFile, "SparkPatchEntry,(1,1,0,),%s,Tiers.Tiers[%d].Object..Items.Items[%d].Object..AbilityClass,0,,BlueprintGeneratedClass'\"%s\"'\n", skillTrees[k], i, j, skills[skillChoice]);
			}
		}
	}
	fprintf(outFile, "### Thank you for choosing mkskillrand! EOF.\n");
	return 0;
}
