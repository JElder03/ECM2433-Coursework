#include <msString.h>

msString msSetString(char *str)
{
	void *msStr;

	/* Allocate memory for new msString */
	if (!(msStr = malloc(sizeof(long int) + strlen(str))))
	{
		msError("Unable to allocate memory for a new msString");
	}

	/* write size of new msString */
	*(long int *)msStr = (long int)strlen(str);

	/* write every char of new msString after its size */
	long int i;
	for (i = 0; i < strlen(str); i++)
	{
		*(char *)(msStr + sizeof(long int) + i) = str[i];
	}
	return msStr;
}

char *msGetString(msString msStr)
{
	char *str;
	long int length = *(long int *)msStr;

	/* allocate memory for new string */
	if (!(str = (char *)malloc(length + 1)))
	{
		msError("Unable to allocate memory for a new string");
	}

	/* copy chars from the msString to new string*/
	long int i;
	msStr += sizeof(long int);
	for (i = 0; i < length; i++)
	{
		str[i] = *(char *)(msStr++);
	}

	/* add null terminator to end of string*/
	str[length] = '\0';

	return str;
}

void msCopy(msString *cpPtr, msString msStr)
{
	/* read length, then increment msStr so it points to its char part */
	long int length = *(long int *)msStr;
	msStr += sizeof(long int);

	/* allocate memory for msString copy */
	if (!(*cpPtr = malloc(sizeof(long int) + length)))
	{
		msError("Unable to allocate memory for a new msString copy");
	}

	/* write the length to msString copy */
	*(long int *)*cpPtr = length;

	/* write every char to msString copy by incrementing the original msStr */
	long int i;
	for (i = 0; i < length; i++)
	{
		*(char *)(*cpPtr + sizeof(long int) + i) = *(char *)(msStr++);
	}
}

void msConcatenate(msString *destination, msString source)
{
	long int length = *(long int *)*destination + *(long int *)source;

	/* resize memory allocated to destination for new concatenated msString */
	if (!(*destination = realloc(*destination, sizeof(long int) + length)))
	{
		msError("Unable to allocate memory for an msString concatenation");
	}

	source += sizeof(long int); /* move source pointer to char part*/

	/* add chars from source to end of destination msString by incrementing source pointer */
	long int i;
	for (i = *(long int *)*destination; i < length; i++)
	{
		*(char *)(*destination + sizeof(long int) + i) = *(char *)(source++);
	}

	/* set destination length to new concatenated length */
	*(long int *)*destination = length;
}

long int msLength(msString msStr)
{
	return *(long int *)msStr;
}

int msCompare(msString msStr1, msString msStr2)
{
	/* compare lengths of msStrings */
	if (*(long int *)msStr1 != *(long int *)msStr2)
	{
		return 1;
	}

	/* move both msStrings to point to their char parts */
	long int length = *(long int *)msStr1;
	msStr1 += sizeof(long int);
	msStr2 += sizeof(long int);

	/* compare each pair of chars in the msStrings */
	long int i;
	for (i = 0; i < length; i++)
	{
		if (*(char *)(msStr1++) != *(char *)(msStr2++))
		{
			return 1;
		}
	}

	return 0; /* strings are the same */
}

int msCompareString(msString msStr, char *str)
{
	/* convert msString to string, then compare with other string */
	char *asString = msGetString(msStr);
	if (strcmp(asString, str))
	{
		free(asString);
		return 1;
	}
	else
	{
		free(asString);
		return 0;
	}
}

void msError(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
