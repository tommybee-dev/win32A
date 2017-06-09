/*
 /* the use of the 32-bit _find() functions to print a list of all files (and their attributes) in the current directory. */
#include "Common.h"
#include <stdio.h>
#include <io.h>
#include <time.h>
#include <direct.h>
#include <conio.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h> // _SH_DENYNO

int printDirList2(char *dir, char *fname) {
	int curdrive;
	char buffer[_MAX_PATH];
	/* file name, change accordingly to other file */
	//char fname[50] = "test.doc";
	char buff[50] = "";
	/* path, change accordingly to other path available on your machine */
	//char dir[50] = "D:\\mycd1\\Ethertest8712";
	struct _finddata_t c_file;
	/* file handle */
	intptr_t hFile;
	/* ---------------------------------------------- */
	printf("Firstly, get the current drive...\n");
	curdrive = _getdrive();
	printf("Current drive is %c:\n\n", curdrive + 'A' - 1);
	/* ----------------------------------------------- */
	printf("Next, get the current working directory...\n");
	printf("Current working directory is: \n");
	if (_getcwd(buffer, _MAX_PATH) == NULL)
		perror("_getcwd() error lol!");
	else
		printf("%s\n\n", buffer);
	/*----------------------------------------------- */
	printf("Change the current working directory...\n");
	_chdir(dir);
	printf("\n");
	/*------------------------------------------------ */
	printf("Current working directory is: \n");
	if (_getcwd(buffer, _MAX_PATH) == NULL)
		perror("_getcwd() error");
	else
		printf("%s\n\n", buffer);
	/* ------------------------------------------------ */
	hFile = _findfirst("*.*", &c_file);
	{
		printf("Listing of *.* files\n\n");
		printf("\nRDO HID SYS ARC TYPE FILE DATE %19c SIZE\n", ' ');
		printf("--- --- --- --- ---- ---- ---- %19c ----\n", ' ');
		printf((c_file.attrib & _A_RDONLY) ? " Y " : " N ");
		printf((c_file.attrib & _A_HIDDEN) ? " Y " : " N ");
		printf((c_file.attrib & _A_SYSTEM) ? " Y " : " N ");
		printf((c_file.attrib & _A_ARCH) ? " Y " : " N ");
		printf((c_file.attrib & _A_NORMAL) ? " Y " : " N ");
		ctime_s(buff, 50, &(c_file.time_write));
		printf(" %-15s %.24s %6d\n", c_file.name, buff, c_file.size);
		/* find the rest of the files */
		while (_findnext(hFile, &c_file) == 0) {
			printf((c_file.attrib & _A_RDONLY) ? " Y " : " N ");
			printf((c_file.attrib & _A_HIDDEN) ? " Y " : " N ");
			printf((c_file.attrib & _A_SYSTEM) ? " Y " : " N ");
			printf((c_file.attrib & _A_ARCH) ? " Y " : " N ");
			printf((c_file.attrib & _A_NORMAL) ? " Y " : " N ");
			ctime_s(buff, 50, &(c_file.time_write));
			printf(" %-15s %.24s %6d\n", c_file.name, buff, c_file.size);
		}
		_findclose(hFile);
	}
	/* check the file existence... 00 - Existence only, 02 - Write-only, 04 - Read-only, 06 - Read and write */
	if ((_access(fname, 0)) != -1)
		printf("\n%s file exists\n", fname);
	else {
		printf("\n%s file not found lor! Error: %d\n", fname, GetLastError());
		/* just exit */
		exit(1);
	}
	/* check the permission */
	printf("\nTest the permission for %s file\n", fname);

	/* if write, then change to read. Must check the write first because file that can be write can also be read but not vice versa */
	if ((_access(fname, 2)) == 0) {
		printf("\n%s file has write permission!\n", fname);
		printf("\nChange to read only permission...\n");
		_chmod(fname, _S_IREAD);
		printf("\nRetest the read only permission...\n");
		if ((_access(fname, 4)) == 0)
			printf("%s file is READ ONLY!\n", fname);
		exit(0);
	}
	/* if not write it should be read permission, then change to write permission*/
	else {
		printf("\n%s file is READ ONLY!\n", fname);
		printf("\nChange to write permission...\n");
		_chmod(fname, _S_IWRITE);
		printf("\nRetest for write permission...");
		if ((_access(fname, 2)) == 0)
			printf("\n%s has write permission!\n", fname);
		exit(0);
	}
	return 0;
}

int printDirList(char *dir, char *fname) {
	int curdrive;
	char buffer[_MAX_PATH];
	/* file name */
	//char fname[20] = "content.doc";
	/* path */
	//char dir[50] = "d:\\test\\testsubtwo\\testsubthree";
	struct _finddata_t c_file;
	/* file handle */
	long hFile;

	/* ---------------------------------------------- */
	printf("Firstly, get the current drive...\n");
	curdrive = _getdrive();
	printf("Current drive is %c:\n\n", curdrive + 'A' - 1);

	/* ----------------------------------------------- */
	printf("Next, get the current working directory...\n");
	printf("Current working directory is: \n");
	if (_getcwd(buffer, _MAX_PATH) == NULL)
		perror("_getcwd error lol!");
	else
		printf("%s\n\n", buffer);

	/*----------------------------------------------- */
	printf("Change the current working directory...\n");
	_chdir(dir);
	printf("\n");

	/*------------------------------------------------ */
	printf("Current working directory is: \n");
	if (_getcwd(buffer, _MAX_PATH) == NULL)
		perror("_getcwd error");
	else
		printf("%s\n\n", buffer);

	/* ------------------------------------------------ */
	hFile = _findfirst("*.*", &c_file);
	{
		printf("Listing of *.* files\n\n");
		printf("\nRDO HID SYS ARC  TYPE  FILE             DATE %19c SIZE\n",
				' ');
		printf("--- --- --- ---  ----  ----             ---- %19c ----\n", ' ');
		printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_ARCH) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_NORMAL) ? " Y  " : " N  ");
		printf("   %-15s %.24s  %6d\n", c_file.name,
				ctime(&(c_file.time_write)), c_file.size);

		/* find the rest of the files */
		while (_findnext(hFile, &c_file) == 0) {
			printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
			printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
			printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
			printf((c_file.attrib & _A_ARCH) ? " Y  " : " N  ");
			printf((c_file.attrib & _A_NORMAL) ? " Y  " : " N  ");
			printf("   %-15s %.24s  %6d\n", c_file.name,
					ctime(&(c_file.time_write)), c_file.size);
		}
		_findclose(hFile);
	}
	/* check the file exist... */
	if ((_access(fname, 0)) != -1)
		printf("\n%s file exists\n", fname);
	else {
		printf("\n%s file not found lor!\n", fname);
		/* just exit */
//		exit(1);
	}

	/* check the permission */
	printf("\nTest the permission for %s file\n", fname);

	/* if write, then change to read.  Must check the write first
	 because file that can be write can also be read but not vice versa */
	if ((_access(fname, 2)) == 0) {
		printf("\n%s file has write permission!\n", fname);
		printf("\nChange to read only permission...\n");
		_chmod(fname, _S_IREAD);

		printf("\nRetest the read only permission...\n");
		if ((_access(fname, 4)) == 0)
			printf("%s file is READ ONLY!\n", fname);
//		exit(0);
	}

	/* if not write it should be read permission, then change to write permission*/
	else {
		printf("\n%s file is READ ONLY!\n", fname);
		printf("\nChange to write permission...\n");
		_chmod(fname, _S_IWRITE);

		printf("\nRetest for write permission...");
		if ((_access(fname, 2)) == 0)
			printf("\n%s has write permission!\n", fname);

//		exit(0);
	}
	return 0;
}

int printFileStat2(char *fileName) {
	struct __stat64 buf;
	int result;
	// change accordingly to other path
	//char fname[50] = "c:\\Windows\\system32\\config\\sam.log";
	char buff[50] = "";
	/* get data associated with a file */
	result = _stat64(fileName, &buf);
	/* test if statistics are valid */
	if (result != 0)
		printf("Problem getting %s file information.\n", fileName);
	else {
		/*dump some of the file information*/
		/*Notice how the structures' elements were accessed*/
		printf("The file : %s\n", fileName);
		printf("Drive : %c:\n", buf.st_dev + 'A');
		printf("File size : %ld bytes\n", buf.st_size);
		/* ctime_s( char* buffer, size_t sizeInBytes, const time_t *time); */
		_ctime64_s(buff, 50, &buf.st_ctime);
		printf("Time created : %s", buff);
		_ctime64_s(buff, 50, &buf.st_atime);
		printf("Last accessed : %s", buff);
		_ctime64_s(buff, 50, &buf.st_mtime);
		printf("Time modified : %s", buff);
		printf("Bit mask : %p\n", &buf.st_mode);
		return 0;
	}

	return result;
}

int printFileStat(char *fileName) {
	struct __stat64 buf;
	int result;
	//char fname[50] = "c:\\WINDOWS\\system32\\config\\sam.log";
	/* get data associated with a file */
	result = _stat64(fileName, &buf);
	/* test if statistics are valid */
	if (result != 0)
		printf("Problem getting %s file information.\n", fileName);
	else {
		/*dump some of the file information*/
		/*Notice how the structures' elements were accessed*/
		printf("The file     : %s\n", fileName);
		printf("Drive        : %c:\n", buf.st_dev + 'A');
		printf("File size    : %ld bytes\n", buf.st_size);
		printf("Time created : %s", _ctime64(&buf.st_ctime));
		printf("Last accessed       : %s", _ctime64(&buf.st_atime));
		printf("Time modified       : %s", _ctime64(&buf.st_mtime));
		printf("Bit mask     : %p\n", &buf.st_mode);
		return 0;
	}

	return result;
}

int createMaskAndOpenFile2(char *fileName) {
	int fh, oldmask;
	/* file in root directory, change accordingly to yours */
	//char test[20] = "C:\\test.txt";
	/* create read-only files: */
	_umask_s(_S_IWRITE, &oldmask);
	/* oldmask = _umask(_S_IWRITE); */
	printf("Oldmask = 0x%.4x\n", oldmask);
	/* create a file with write permission */
	_sopen_s(&fh, fileName, _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
	/* fh = _creat(test, _S_IWRITE); */
	if (fh == -1)
		printf("Couldn't create %s file!\n", fileName);
	else {
		printf("%s file successfully created.\n", fileName);
		_close(fh);
	}
	/* try opening file for write */
	/* fh = _open(test, _O_WRONLY); */
	_sopen_s(&fh, fileName, _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
	if (fh == -1)
		printf("%s opening failed!\n", fileName);
	else {
		printf("%s opening succeeded!\n", fileName);
		if (_close(fh) == 0)
			printf("%s closed successfully!\n", fileName);
	}
	printf("Oldmask = 0x%.4x\n", oldmask);
	return 0;
}

int createMaskAndOpenFile(char *fineName) {
	int fh, oldmask;
	/* file in current working directory,  change accordingly to yours */
	//char test[20] = "test.txt";
	/* create read-only files: */
	oldmask = _umask(_S_IWRITE);
	printf("Oldmask = 0x%.4x\n", oldmask);
	/*create a file with write permission */
	fh = _creat(fineName, _S_IWRITE);
	if (fh == -1)
		printf("Couldn't create %s file!\n", fineName);
	else {
		printf("%s file successfully created.\n", fineName);
		_close(fh);
	}
	/* try opening file for write */
	fh = _open(fineName, _O_WRONLY);
	if (fh == -1)
		printf("%s opening failed!\n", fineName);
	else {
		printf("%s opening succeeded!\n", fineName);
		if (_close(fh) == 0)
			printf("%s closed successfully!\n", fineName);
	}
	printf("Oldmask = 0x%.4x\n", oldmask);
	return 0;

}

int accessAndRemoveFile(char *obj, char *newobj) {
	int result;

	/* check for existence */
	if ((_access(obj, 0)) != -1)
		printf("%s file exists\n", obj);
	else
		printf("%s file does not exist lol!\n", obj);
	/* check for read/write permission */
	if ((_access(obj, 2)) != -1)
		printf("%s file has write permission\n", obj);
	if ((_access(obj, 4)) != -1)
		printf("%s file has read permission\n", obj);
	if ((_access(obj, 6)) != -1)
		printf("%s file has write and read permission\n\n", obj);
	/* make file read-only: */
	if (_chmod(obj, _S_IREAD) == -1)
		perror("File not found lol!\n");
	else {
		printf("The file mode is changed to read-only\n");
		_chmod(obj, _S_IREAD);
	}
	if ((_access(obj, 4)) != -1)
		printf("%s file has read permission\n", obj);
	/* change back to read/write */
	if (_chmod(obj, _S_IWRITE) == -1)
		perror("file not found lol!\n");
	else {
		printf("\nThe file\'s mode is changed to read/write\n");
		_chmod(obj, _S_IWRITE);
	}
	if ((_access(obj, 2)) != -1)
		printf("%s file has write permission\n", obj);
	/* attempt to rename file */
	result = rename(obj, newobj);
	if (result != 0)
		printf("\nCould not rename %s\n", obj);
	else
		printf("\n%s file has been renamed to\n %s\n", obj, newobj);
	/* remove the file */
	if (remove(newobj) == -1)
		printf("\nCould not delete %s lol!\n", newobj);
	else
		printf("\nOoops! %s file has been deleted lol!\n", newobj);
	return 0;

}

int printMakeSplitPath(const char *driveLetter, const char *path,
		const char *fileName, const char* fileExt) {
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	// change the path accordingly to yours
	//_makepath(path_buffer, "g", "\\Testdir\\myexample\\", "testfile", "txt");
	_makepath(path_buffer, driveLetter, path, fileName, fileExt);
	printf("Path created with _makepath(): %s\n", path_buffer);
	_splitpath(path_buffer, drive, dir, fname, ext);
	printf("Path extracted with _splitpath():\n");
	printf("  Drive: %s\n", drive);
	printf("  Dir: %s\n", dir);
	printf("  Filename: %s\n", fname);
	printf("  Ext: %s\n", ext);
	return 0;
}

void DisplayFullPath(char *relPath) {
	/* a buffer */
	char full[_MAX_PATH];
	if (_fullpath(full, relPath, _MAX_PATH) != NULL)
		printf("The full path is: %s\n", full);
	else
		printf("Invalid path\n");
}

int changFileSize2(const char *fname) {
	int fhdl, result;
	/* make sure this file is there, else change accordingly */
	//char fname[20] = "C:\\data.txt";
	/* open a file */
	if (_sopen_s(&fhdl, fname, _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE)
			== 0) {
		printf("%s file length before running _chsize(): %ld\n", fname,
				_filelength(fhdl));
		/* change the file size */
		printf("Executing _chsize(fhdl, 123456)...\n");
		if ((result = _chsize(fhdl, 123456)) == 0)
			printf("%s file size successfully changed!\n", fname);
		else
			printf("Problem in changing the %s size. Error %d\n", fname,
					GetLastError());
		/* new size */
		printf("%s file length after changing the size: %ld\n", fname,
				_filelength(fhdl));
		/* close the file handle */
		_close(fhdl);
	}
	return 0;
}

int changFileSize(const char *fname) {
	int fhdl, result;

	printf("file name is %s\r\n", fname);

	/* open a file */
	if ((fhdl = _open(fname, _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE)) != -1) {
		printf("%s file length before running _chsize(): %ld\n", fname,
				_filelength(fhdl));
		/* change the file size */
		printf("Executing _chsize(fhdl, 123456)...\n");
		if ((result = _chsize(fhdl, 123456)) == 0)
			printf("%s file size successfully changed!\n", fname);
		else
			printf("Problem in changing the %s size\n", fname);
		/* new size */
		printf("%s file length after changing the size: %ld\n", fname,
				_filelength(fhdl));
		/* close the file handle */
		_close(fhdl);
	}
	return 0;
}

int printFileAttr(const char *path) {
// for XP, char path[50] = "C:\\Windows\\System32\\config";
	//char path[50] = "C:\\WINNT\\System32\\config";
	struct _finddata_t c_file;
	long hFile;

	printf("Change to %s\n", path);
	if (_chdir(path))
		printf("Unable to locate the directory: %s\n", path);
	else

		/* find first in the current directory */
		/* hFile = (long) _findfirst("*.*", &c_file); */
		hFile = _findfirst("*.*", &c_file);

	/* list the files... */
	printf("Listing of files in the directory %s\n\n", path);
	printf("\nRDO HID SYS ARC  FILE         DATE %25c SIZE\n", ' ');
	printf("--- --- --- ---  ----         ---- %25c ----\n", ' ');
	printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
	printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
	printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
	printf((c_file.attrib & _A_ARCH) ? " Y  " : " N  ");
	printf(" %-12s %.24s  %9ld\n", c_file.name, ctime(&(c_file.time_write)),
			c_file.size);

	/* find the rest of the files */
	while (_findnext(hFile, &c_file) == 0) {
		printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
		printf((c_file.attrib & _A_ARCH) ? " Y  " : " N  ");
		printf(" %-12s %.24s  %9ld\n", c_file.name, ctime(&(c_file.time_write)),
				c_file.size);
	}
	_findclose(hFile);

	return 0;
}
/*
 * AboutFile.c
 *
 * Created on: 2017. 6. 8.
 * Author: tommybee
 */

