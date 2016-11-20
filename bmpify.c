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

	// get input file size
	int64_t inputFileSize = fileSize(inputFile);

	// can now write output file header
	writeFileHeader(outputFile, inputFileSize);

	// determine image dimentions
	int64_t pixelCount = inputFileSize / (PIXEL_BITS / 8);
	int32_t width, height;
	width = pixelCount / 2;
	height = pixelCount / 2;
	int32_t rowSize = width * (PIXEL_BITS / 8);

	printf("Input size: %ldB, pixel count: %ld, dimentions: %dx%d, row size: %dB\n",
		inputFileSize, pixelCount, width, height, rowSize);

	// can now write output bitmap header
	writeBitmapHeader(outputFile, width, height);

	// TODO read/write pixels

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
	// file header struct
	fileHeader_t fileHeader;
	fileHeader.signature = FH_WINDOWS_SIG;
	fileHeader.fileSize = sizeof(fileHeader_t) + sizeof(bitmapHeader_t) + inputFileSize;
	fileHeader.reservedA = FH_RESERVED_A;
	fileHeader.reservedB = FH_RESERVED_B;
	fileHeader.offset = sizeof(fileHeader_t) + sizeof(bitmapHeader_t);

	// write struct to file
	fwrite(&fileHeader, 1, sizeof(fileHeader_t), outputFile);
}

void writeBitmapHeader(FILE *outputFile, int32_t width, int32_t height)
{
	// bitmap header struct
	bitmapHeader_t bitmapHeader;
	bitmapHeader.headerSize = BH_HEADER_SIZE;
	bitmapHeader.width = width;
	bitmapHeader.height = height;
	bitmapHeader.planes = BH_PLANES;
	bitmapHeader.bitCount = PIXEL_BITS;
	bitmapHeader.compression = BH_COMPRESSION;
	bitmapHeader.imageSize = BH_IMAGE_SIZE;
	bitmapHeader.xPPM = BH_X_PPM;
	bitmapHeader.yPPM = BH_Y_PPM;
	bitmapHeader.colourPallet = BH_COLOUR_PALLET;
	bitmapHeader.importantColours = BH_IMPORTANT_COLOURS;

	// write struct to file
	fwrite(&bitmapHeader, 1, sizeof(bitmapHeader_t), outputFile);
}
