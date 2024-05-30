#include <coursework.h>

int main(int argc, char **argv)
{
	testReadBytes();
	testInputOutput(argc, argv);
	testMsString();
}

int testReadBytes(void)
{
	printf("\nSTARTING READ BYTES TESTS:\n");
	char bytes1[] = {10, 20, 30, 145};
	char bytes2[] = {200};
	printBytes(&bytes1, 4);
	printBytes(&bytes2, 5);
	printBytes(&bytes1, 0);
	printBytes(&bytes2, -1);
	return 0;
}

int testInputOutput(int argc, char **argv){
	printf("\nSTARTING INPUT OUTPUT TESTS:\n");
	if (argc != 3)
	{
		fprintf(stderr, "Incorrect number of arguments provided\n");
		exit(1);
	}
	else
	{
		inputOutput(argv[1], argv[2]);
	}
	printf("INPUT OUTPUT RAN SUCCESSFULLY\n");
	return 0;
}

int testMsString(void)
{
	printf("\nSTARTING MS_STRING TESTS:\n");
	msString ms = msSetString("Hello");
	msString ms2 = msSetString(" World!");
	msString mscopy = NULL;

	char *str; /* to store strings returned from msGetString() for future memory freeing */

	str = msGetString(ms); /* storing msGetString() return pointer to free later - repeated for every msGetString() call*/
	printf("String |%s| is %d characters long (%p).\n", str, msLength(ms), ms);
	free(str); /* free dynamically allocated string */

	msCopy(&mscopy, ms);
	str = msGetString(mscopy);
	printf("Copied string |%s| is %d characters long (%p).\n", str, msLength(mscopy), mscopy);
	free(str);

	printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
	printf("Compare ms with ms2: %d\n", msCompare(ms, ms2));
	printf("Compare ms with Hello: %d\n", msCompareString(ms, "Hello"));
	printf("Compare ms with HelloX: %d\n", msCompareString(ms, "HelloX"));
	printf("Compare ms with Hella: %d\n", msCompareString(ms, "Hella"));

	msConcatenate(&mscopy, ms2);
	str = msGetString(mscopy);
	printf("Concatenated string |%s| is %d characters long (%p).\n", str, msLength(mscopy), mscopy);
	free(str);

	/* freeing memory for dynamically allocated msStrings */
	free(ms);
	free(ms2);
	free(mscopy);
	return 0;
}
