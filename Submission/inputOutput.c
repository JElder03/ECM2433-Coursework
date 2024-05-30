#include <inputOutput.h>

int inputOutput(char *in, char *out)
{
	char *str = NULL;
	FILE *fpIn;
	FILE *fpOut;

	if ((fpIn = fopen(in, "r")) == NULL)
	{
		fprintf(stderr, "Unable to read file: %d: %s\n", errno, strerror(errno));
		exit(1);
	}

	readStr(&str, fpIn);
	close(fpIn);
	reverseStr(&str);

	if ((fpOut = fopen(out, "w")) == NULL)
	{
		fprintf(stderr, "Unable to write to file: %d: %s\n", errno, strerror(errno));
		exit(1);
	}

	fputs(str, fpOut);
	close(fpOut);
	free(str);

	return (0);
}

void readStr(char **str, FILE *fp)
{
	char c;
	int numCh = 0;
	int size = 10;
	*str = malloc(size);

	if (*str == NULL)
	{
		fprintf(stderr, "Not enough memory to read the string from input file\n");
		exit(1);
	}

	while ((c = fgetc(fp)) != EOF && c != '\n')
	{
		if (size <= numCh)
		{
			size += 10;
			*str = realloc(*str, size);
			if (*str == NULL)
			{
				fprintf(stderr, "Not enough memory to read the string from input file\n");
				exit(1);
			}
		}
		(*str)[numCh++] = c;
	}

	if (fgetc(fp) != EOF)
	{
		fprintf(stderr, "Input file is formatted incorrectly\n");
		exit(1);
	}
	(*str)[numCh++] = '\0';
}

void reverseStr(char **str)
{
	int length = strlen(*str);
	char buffer;
	int i = 0;

	while (i < length)
	{
		buffer = (*str)[i];
		(*str)[i] = (*str)[length - 1];
		(*str)[length - 1] = buffer;
		i++;
		length--;
	}
}
