#ifndef BMPIFY_H
#define BMPIFY_H

#ifdef _WIN32

typedef int int32_t;
typedef short int16_t;
#define PACK(__Declaration__) __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))

#else

#include <sys/types.h>
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))

#endif

PACK(struct fileHeader
{
	int16_t signature;
	int32_t fileSize;
	int16_t reservedA;
	int16_t reservedB;
	int32_t offset;
});

PACK(struct bitmapHeader
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

typedef struct fileHeader fileHeader_t;
typedef struct bitmapHeader bitmapHeader_t;

#endif
