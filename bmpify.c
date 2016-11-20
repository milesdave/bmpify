#include <stdio.h>
#include "bmpify.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s input-file output-file\n", argv[0]);
		return 1;
	}

	return 0;
}
