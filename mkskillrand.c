#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Skills.h"
#include <bl3mod.h>

/* MKSKILLRAND - 4 TREE EDITION */

FILE* outFile;

int main(int argc, char** argv) {
	char* line;
	int i;
	int j;
	int k;
	int skillChoice;
	int numTiers = 6;
	int numSkills = 3;
	int numTrees = 16;
	char selector[512];
	char replacement[512];
	char* filename = "";
	int choice;
	srand(time(NULL));
	if(argc < 2) {
		filename = "skill_randomizer.txt";
	}
	else {
		filename = argv[1];
	}
	printf("MKSKILLRAND Skill randomizer generator. Trees = 4; output file = %s\n", filename);
	outFile = fopen(filename, "w");
	if(!outFile) {
		printf("MKSKILLRAND Failed to open output file\n");
		exit(1);
	}
	fprintf(outFile, fileHeader);
	for(k = 0; k < numTrees; k++) {
		for(i = 1; i < numTiers + 1; i++) {
			for(j = 0; j < numSkills; j++) {
				choice = rand() % (listNumSkills4);
				/* In theory... this shouldn't take up more than half a K per entry. */
				memset(selector, 0x00, 512);
				memset(replacement, 0x00, 512);
				sprintf(selector, "Tiers.Tiers[%d].Object..Items.Items[%d].Object..AbilityClass", i, j);
				sprintf(replacement, "BlueprintGeneratedClass'\"%s\"'", end_object_c(skills[choice]));
				line = regular_hotfix(MOD_TYPE_PATCH, extract_object(skillTrees[k]), "ItemFrameName", "", 0);
				fwrite(line, sizeof(char), strlen(line), outFile);
				line = regular_hotfix(MOD_TYPE_PATCH, extract_object(skillTrees[k]), "AbilityClass", replacement, 0);
				fwrite(line, sizeof(char), strlen(line), outFile);
			}
		}
	}
	fprintf(outFile, fileFooter);
	printf("Skill randomizer processing complete.\n");
	return 0;
}
