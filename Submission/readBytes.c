#include <readBytes.h>

void printBytes(void *ptr, int numBytes)
{
	printf("Starting at memory address %p:\n", ptr);

	int i;
	for (i = 0; i < numBytes; i++)
	{
		/* read a single byte from ptr as an unsigned char then increment */
		printf("%03d: %3d\n", i + 1, (*(unsigned char *)ptr++));
	}
}