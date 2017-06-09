#include "Common.h"

#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

int testDirectory(void) {
	int chr, drive, curdrive;
	static char path[_MAX_PATH];
	char buffer[_MAX_PATH];
	char newdir[50] = "\\testdir";
	char path1[50] = "C:\\Windows\\System32\\config";
	//char path1[50] = "C:\\WINNT\\System32\\config";
	//char path1[50] = "C:\\DEV";

	/* save current drive. */
	curdrive = _getdrive();
	printf("Available drives in this machine are: \n");

	/* if we can switch to the drive, it exists. */
	for (drive = 1; drive <= 26; drive++)
		if (!_chdrive(drive))
			printf("%c: ", drive + 'A' - 1);

	printf("\n\nType drive letter to check: ");
	chr = _getch();
	if (chr == 27)
		printf("Illegal drive input\n");
	if (isalpha(chr))
		_putch(chr);
	if (_getdcwd(toupper(chr) - 'A' + 1, path, _MAX_PATH) != NULL)
		printf("\nCurrent directory on that drive is:\n%s\n", path);

	/* restore original drive. */
	_chdrive(curdrive);

	/* get the current working directory */
	if (_getcwd(buffer, _MAX_PATH) == NULL)
		perror("_getcwd error");
	else
		printf("\nCurrent working directory is: %s\n", buffer);

	/* create a directory and then delete */
	if (_mkdir(newdir) == 0) {
		printf("\nDirectory %s was successfully created\n", newdir);
		system("dir \\testdir");

		if (_rmdir("\\testdir") == 0)
			printf("\nDirectory %s was successfully removed\n", newdir);
		else
			printf("\nProblem removing directory %s\n", newdir);
	} else
		printf("\nProblem creating directory %s\n", newdir);

	/* uses _chdir() function to verify that a given directory exists */
	printf("\n");
	printf("Change directory........\n");
	if (_chdir(path1))
		printf("Unable to locate the directory: %s\n", path1);
	else
		system("dir *.log /a");
	printf("\n");
	return 0;
}

int checkDirectory(void) {
	int chr, drive, curdrive;
	static char path[_MAX_PATH];
	char buffer[_MAX_PATH];
	char newdir[50] = "\\testdir";
	// char path1[50] = "C:\\WINNT\\System32\\config";
	char path1[50] = "C:\\Windows\\System32\\config";
	/* save current drive. */
	curdrive = _getdrive();
	printf("Available drives in this machine are: \n");
	/* if we can switch to the drive, it exists. */
	for (drive = 1; drive <= 26; drive++)
		if (!_chdrive(drive))
			printf("%c: ", drive + 'A' - 1);
	printf("\n\nType drive letter to check: ");
	chr = _getch();
	if (chr == 27)
		printf("Illegal drive input\n");
	if (isalpha(chr))
		_putch(chr);
	if (_getdcwd(toupper(chr) - 'A' + 1, path, _MAX_PATH) != NULL)
		printf("\nCurrent directory on that drive is:\n%s\n", path);
	/* restore original drive. */
	_chdrive(curdrive);
	/* get the current working directory */
	if (_getcwd(buffer, _MAX_PATH) == NULL)
		perror("_getcwd error");
	else
		printf("\nCurrent working directory is: %s\n", buffer);
	/* create a directory and then delete */
	if (_mkdir(newdir) == 0) {
		printf("\nDirectory %s was successfully created\n", newdir);
		system("dir \\testdir");
		if (_rmdir("\\testdir") == 0)
			printf("\nDirectory %s was successfully removed\n", newdir);
		else
			printf("\nProblem removing directory %s\n", newdir);
	} else
		printf("\nProblem creating directory %s\n", newdir);
	/* uses _chdir() function to verify that a given directory exists */
	printf("\n");
	printf("Change directory........\n");
	if (_chdir(path1))
		printf("Unable to locate the directory: %s\n", path1);
	else
		system("dir *.log /a");
	printf("\n");
	return 0;
}

