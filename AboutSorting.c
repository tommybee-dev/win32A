#include "Common.h"

#include <search.h>
#include <string.h>


/* a compare function prototype */
static int compare(char **arg1, char *arg2[]);

int SortingTest(int argc, char *argv[], char *key) {
	char **result;
	//char *key = "red";
	int i;

	//result = NULL;
	//if (argc == 1) {
	//	printf("Usage: %s <some strings> \n", argv[0]);
	//	printf("Example: %s blue yellow red black white\n", argv[0]);
		//exit(1);
	//}
	/* sort using qsort algorithm */
	qsort((void *) argv, (size_t) argc, sizeof(char *),
			(int (*)(const void*, const void*)) compare);

	/* output the sorted list */
	for (i = 0; i < argc; ++i)
		printf("%s ", argv[i]);
	/* find the word "cat" using a binary search algorithm */
	result = (char **) bsearch((char *) &key, (char *) argv, argc,
			sizeof(char *), (int (*)(const void*, const void*)) compare);
	if (result)
		printf("\n\'%s\' word found at address: %p\n", key, result);
	else
		printf("\n\'%s\' word not found!\n", key);

	return 0;
}

int compare(char *arg1[], char *arg2[]) {
	/* compare all of both strings */
	return _strcmpi(*arg1, *arg2);
}
