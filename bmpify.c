#define _DEFAULT_SOURCE
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmpify.h"

int main(int argc, char *argv[])
{
	const char *outputFileName;

	if(argc < 2)
	{
		printf("Usage: %s input-file [output-file]\n\n"
			"  input-file        file used to generate the bitmap image\n"
			"  output-file       optional filename for the bitmap image\n"
			"                    default file if none specified is \"%s\"\n",
			argv[0], defaultOutputFileName);
		return 1;
	}

	// use default output file name if none provided
	outputFileName = argc == 2 ? defaultOutputFileName : argv[2];

	FILE *inputFile, *outputFile;

	// open input file
	if((inputFile = fopen(argv[1], "rb")) == NULL)
	{
		perror(argv[1]);
		return 1;
	}

	// open output file
	if((outputFile = fopen(outputFileName, "wb+")) == NULL)
	{
		perror(outputFileName);
		fclose(inputFile);
		return 1;
	}

	// get input file size
	int64_t inputFileSize = fileSize(inputFile);

	// can now write output file header
	writeFileHeader(outputFile, inputFileSize);

	// determine image dimentions
	int64_t pixelCount = inputFileSize / PIXEL_BYTES;
	int32_t width, height;
	width = height = (int32_t)round(sqrt(pixelCount));
	int32_t rowSize = width * PIXEL_BYTES;
	int32_t paddedRowSize = rowSize % 4 == 0 ? rowSize : rowSize + PIXEL_BYTES;

	printf("Input: %ldB, pixels: %ld (%d x %d x %d), bytes/row: %dB (%dB)\n"
		"Output: %s\n",
		inputFileSize, pixelCount, width, height, PIXEL_BITS, rowSize, paddedRowSize,
		outputFileName);

	// can now write output bitmap header
	writeBitmapHeader(outputFile, width, height);

	// pixel buffer
	char *pixels = calloc(1, paddedRowSize);

	// read/write pixels as rows in the image
	for(int i = 0; i < height; i++)
	{
		fread(pixels, 1, rowSize, inputFile);
		fwrite(pixels, 1, paddedRowSize, outputFile);
	}

	free(pixels);
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
