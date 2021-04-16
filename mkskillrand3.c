#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Skills.h"
#include <bl3mod.h>

/* MKSKILLRAND - 4 TREE EDITION */

FILE* outFile;

int main(int argc, char** argv) {
	int i;
	int j;
	int k;
	int numTiers = 6;
	int numSkills = 3;
	int numTrees = 12;
	char selector[512];
	char replacement[512];
	char* filename = "";
	char* line;
	srand(time(NULL));
	if(argc < 2) {
		filename = "skill_randomizer3.txt";
	}
	else {
		filename = argv[1];
	}
	printf("MKSKILLRAND Skill randomizer generator. Trees = 3; output file = %s\n", filename);
	outFile = fopen(filename, "w");
	if(!outFile) {
		printf("MKSKILLRAND Failed to open output file\n");
		exit(1);
	}
	fprintf(outFile, fileHeader);
	
	for(k = 0; k < numTrees; k++) {
		for(i = 1; i < numTiers + 1; i++) {
			for(j = 0; j < numSkills; j++) {
				/*
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
				fprintf(outFile, "SparkPatchEntry,(1,1,0,),%s.%s,Tiers.Tiers[%d].Object..Items.Items[%d].Object..ItemFrameName,0,,\r\n", classPath, classEnd, i, j);
				fprintf(outFile, "SparkPatchEntry,(1,1,0,),%s.%s,Tiers.Tiers[%d].Object..Items.Items[%d].Object..AbilityClass,0,,BlueprintGeneratedClass'\"%s.%s_C\"'\r\n", classPath, classEnd, i, j, skillEnd, skillEnd);
				*/
				bzero(selector, 512);
				bzero(replacement, 512);
				sprintf(selector, "Tiers.Tiers[%d].Object..Items.Items[%d].Object..AbilityClass", i, j);
				sprintf(replacement, "BlueprintGeneratedClass'\"%s\"'", end_object_c(skills[rand() % (listNumSkills3)]));
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
