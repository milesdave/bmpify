#define _DEFAULT_SOURCE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "bmpify.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s input-file output-file\n", argv[0]);
		return 1;
	}

	FILE *inputFile, *outputFile;

	// open input file
	if((inputFile = fopen(argv[1], "r")) == NULL)
	{
		perror(argv[1]);
		return 1;
	}

	// file header
	fileHeader_t fileHeader;
	fileHeader.signature = FH_WINDOWS_SIG;
	fileHeader.reservedA = FH_RESERVED_A;
	fileHeader.reservedB = FH_RESERVED_B;

	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
