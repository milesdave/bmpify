#ifndef BMPIFY_H
#define BMPIFY_H

#ifdef _WIN32

#define PACK(__Declaration__) __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int int64_t;

#else

#include <sys/types.h>
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))

#endif

/* change both of these to change the bits-per-pixel */
#define PIXEL_BITS 32
#define pixelType int32_t

#define FH_WINDOWS_SIG 0x4D42
#define FH_RESERVED_A 0
#define FH_RESERVED_B 0
PACK(struct _fileHeader
{
	int16_t signature;
	int32_t fileSize;
	int16_t reservedA;
	int16_t reservedB;
	int32_t offset;
});

#define BH_HEADER_SIZE 40
#define BH_PLANES 0
#define BH_COMPRESSION 0
#define BH_IMAGE_SIZE 0
#define BH_X_PPM 0
#define BH_Y_PPM 0
#define BH_COLOUR_PALLET 0
#define BH_IMPORTANT_COLOURS 0
PACK(struct _bitmapHeader
{
	int32_t headerSize;
	int32_t width;
	int32_t height;
	int16_t planes;
	int16_t bitCount;
	int32_t compression;
	int32_t imageSize;
	int32_t xPPM;
	int32_t yPPM;
	int32_t colourPallet;
	int32_t importantColours;
});

typedef struct _fileHeader fileHeader_t;
typedef struct _bitmapHeader bitmapHeader_t;

int64_t fileSize(FILE *file);
void writeFileHeader(FILE *outputFile, int64_t inputFileSize);
void writeBitmapHeader(FILE *outputFile, int32_t width, int32_t height);

#endif
