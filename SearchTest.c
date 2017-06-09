#include "Common.h"
#include "stdbool.h"
#include <direct.h>
#include <ctype.h>

#include <io.h>


/* prototype for recursive function */
static void FindThePath(TCHAR*, TCHAR*, TCHAR*);

/* filename stripping */
static void TheRightside(TCHAR *str, size_t num) {
	size_t i = _tcslen(str);
	size_t chs = 0, chr = 0;
	/* may use malloc() */
	TCHAR *hld = (TCHAR*)malloc(sizeof(TCHAR) * (num + 1));

	if ((i > num) || (i == num)) {
		for (chs = (i - num); chs < i; chs++) {
			hld[chr] = str[chs];
			++chr;
		}
		hld[num] = '\0';
		for (chs = 0; chs < (num + 1); chs++) {
			str[chs] = hld[chs];
		}
	}
	/* don't forget to free() up if using malloc() */
	//delete [ ] hld;
	free(hld);
}

/* test the searched string/filename */
static BOOL TestTheStrings(TCHAR *str1, TCHAR *str2) {
	char *mp, *cp;
	size_t x1 = 0;
	size_t i = 0;
	BOOL ret = TRUE;

	x1 = _tcslen(str1);
	if (_tcslen(str2) != (unsigned) x1) {
		ret = FALSE;
	} else {
		for (i = 0; i < x1; i++) {
			if (str1[i] != str2[i])
				ret = FALSE;
		}
	}

	while ((*str2) && (*str1 != '*')) {
		if ((*str1 != *str2) && (*str1 != '?')) {
			return 0;
		}
		str1++;
		str2++;
	}
	while (*str2) {
		if (*str1 == '*') {
			if (!*++str1) {
				return 1;
			}
			mp = str1;
			cp = str2 + 1;
		} else if ((*str1 == *str2) || (*str1 == '?')) {
			str1++;
			str2++;
		} else {
			str1 = mp;
			str2 = cp++;
		}
	}
	while (*str1 == '*') {
		str1++;
	}
	return !*str1;
return ret;
}
/* search and construct the path */
void FindThePath(TCHAR *root, TCHAR *file, TCHAR *buffer) {
	HANDLE hFind;
	BOOL ok;
	WIN32_FIND_DATA fd;

	TCHAR start[_MAX_PATH];
	TCHAR dir[_MAX_PATH];
	/* search flag */
	BOOL found = FALSE;
	size_t tlen;

	TCHAR test[_MAX_PATH];
	/* using test as a temp location */
	_tcscpy(test, buffer);
	/* get the length of the file name */
	tlen = _tcslen(file);
	/* strip off possible filename if it is in the buffer */
	TheRightside(test, tlen);
	/* test for it */
	if (TestTheStrings(test, file))
	/* return if it is there...no need to look further */
	{
		return;
	}

	/* if they passed a valid string for the root */
	if (_tcslen(root) > 0) {
		/* modify it to search for all files/folders.... */
		_tcscpy(start, root);
		_tcscat(start, "\\*");
	}

	for (hFind = FindFirstFile(start, &fd), ok = 1;
			hFind != INVALID_HANDLE_VALUE && ok; ok = FindNextFile(hFind, &fd)) {
	// bitwise AND to test the returned fileattributes
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			/* assuming it is a dir so copy over */
			_tcscpy(dir, fd.cFileName);
			/* make sure it is not the default parent directory...*/
			if ((TestTheStrings(dir, ".") == false)) {
				/* or current working directory, copying this over results in infinite recursion */
				if ((TestTheStrings(dir, "..") == false)) {
					if (found == false)
					/* if we have not found the file in this current call, then make a call */
					{
						/* constructs the path or you can try the _fullpath() */
						_tcscpy(test, root);
						_tcscat(test, "\\");
						_tcscat(test, dir);

						/*and recurse through them.....*/
						FindThePath(test, file, buffer);
					}/* end found */
				}/* end .. test */
			}/* end . test */
		}/* end dir test */

		/* bitwise AND to check for file flag */
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_DIRECTORY
				| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN) {
			/* if we have a file is it the one we want? */
			found = TestTheStrings(file, fd.cFileName);
			if (found == true) {
				/* if it is, then create the full path name for it and copy into the buffer */
				_tcscpy(buffer, root);
				_tcscat(buffer, "\\");
				_tcscat(buffer, fd.cFileName);
				printf("%s\n", buffer);

				/*-----------------------------------------------------------------*/
				/* other routines can be implemented/called here for the found files */
				/* such as delete, rename, replace, search the file contents,       */
				/* move, append, create a file, change the file attributes etc...   */
				/*-----------------------------------------------------------------*/

			}/* end found test */
		}/* end archive test */
	}/* end for */

	/* 18 = ERROR_NO_MORE_FILES, that is if other than no more files... */
	/* Check the error if any */
	if (GetLastError() != 18)
		printf("FindFile() error: %d\n", GetLastError());
	if (hFind != INVALID_HANDLE_VALUE) {
		BOOL ok = FindClose(hFind);
		if (!ok)
			/* check the last error if any, very good for troubleshooting/debug */
			printf("FindClose() error: %d", GetLastError());
	}
}

/* the main() program */
int SearchTest(int argc, char *argv[], TCHAR *driv) {
	TCHAR buffer[_MAX_PATH];
	ULONG DriveMask;

	/*Some prompt*/
	printf("Example usage: %s <test.txt> or <test.*> or <*.txt> or <*.*>\n", argv[0]);
	printf("It is case sensitive!\n\n");

	/* get the drives bit masks...1 is available, 0 is not available */
	/* A = least significant bit... */
	DriveMask = _getdrives();
	/* if something wrong */
	if (DriveMask == 0)
		printf("_getdrives() failed with failure code: %d\n", GetLastError());

	while (DriveMask) {
		printf("Found %s and start digging...\n", driv);
		if (DriveMask & 1)
			printf(driv);
		/* for every found drive...do the file search */
		FindThePath(driv, argv[1], buffer);
		/* pointer increment */
		++driv[0];
		/* shift the bit masks binary to the right and repeat, means go to the next found drive */
		DriveMask >>= 1;
	}
	return 0;
}
