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

	// open output file
	if((outputFile = fopen(argv[2], "w+")) == NULL)
	{
		perror(argv[2]);
		fclose(inputFile);
		return 1;
	}

	// write file header
	writeFileHeader(outputFile, fileSize(inputFile));

	fclose(inputFile);
	fclose(outputFile);
	return 0;
}

int64_t fileSize(FILE *file)
{
	// seek to end
	fseek(file, 0, SEEK_END);

	// get offset
	int64_t size = ftell(file);

	// go back to original offset
	rewind(file);

	return size;
}

void writeFileHeader(FILE *outputFile, int64_t inputFileSize)
{
	// file header
	fileHeader_t fileHeader;
	fileHeader.signature = FH_WINDOWS_SIG;
	fileHeader.fileSize = sizeof(fileHeader_t) + sizeof(bitmapHeader_t) + inputFileSize;
	fileHeader.reservedA = FH_RESERVED_A;
	fileHeader.reservedB = FH_RESERVED_B;
	fileHeader.offset = sizeof(fileHeader_t) + sizeof(bitmapHeader_t);

	// write to file
	fwrite(&fileHeader, 1, sizeof(fileHeader_t), outputFile);
}
