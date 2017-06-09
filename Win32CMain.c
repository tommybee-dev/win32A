#include "Common.h"


static void sortingTest()
{
	int ret;
	int argc = 6;
	char key[50] = "blu1e";
	char **argv = (char**)malloc(argc * sizeof(char*));;


	argv[0] = "mcruntime";
	argv[1] = "blue";
	argv[2] = "yellow";
	argv[3] = "red";
	argv[4] = "black";
	argv[5] = "white";

	ret = SortingTest(argc, argv, key);

	free(argv);
	argv = NULL;
}

static void searchingTest()
{
	int ret;
	int argc = 3;
	TCHAR mydrives[] = "C:";
	char **argv = (char**)malloc(argc * sizeof(char*));;

	argv[0] = "searchingTest";
	argv[1] = "*.txt";
	//argv[1] = ".project";

	ret = SearchTest(argc, argv, mydrives);

	free(argv);
	argv = NULL;
}

int main() {
	const char *path = "C:\\DEV\\Tools\\QGIS-Portable-CH\\qgis-portable-ch";
	const char *fname = "C:\\DEV\\MyProject\\Temp\\data.txt";
	char *fnameerr = "C:\\DEV\\MyProject\\Temp\\data2.txt";
	const char *fname2 = "AboutFile.obj";
	const char *fname3 = "\\AboutFile.obj";
	const char *fname4 = ".\\AboutFile.obj";
	char obj[50] = "C:\\DEV\\MyProject\\Temp\\robots.txt";
	char newobj[50] = "C:\\DEV\\MyProject\\Temp\\human.txt";
	char filename[50] = "C:\\Windows\\System32\\config\\SAM.LOG";
	char dir[50] = "C:\\DEV\\MyProject\\workspace";
	char fname5[50] = "WsockTest.c";
	char *ampm = "AM";


	int argc = 6;
	int ret;

	char **argv = (char**)malloc(argc * sizeof(char*));;


	//ret = printLogicalDrive();
	//ret = printLocalSpaces();
	//ret = testDirectory();
	//ret = checkDirectory();
	//ret = printFileAttr(path);
	//ret = changFileSize(fname);
	//ret = changFileSize2(fname);
	//DisplayFullPath(fname2);
	//DisplayFullPath(fname3);
	//DisplayFullPath(fname4);
	//ret = printMakeSplitPath("c", "\\DEV\\MyProject\\Temp\\", "testfile", "txt");
	//ret = accessAndRemoveFile(obj, newobj);
	//ret = createMaskAndOpenFile(obj);
	//ret = createMaskAndOpenFile2(obj);
	//ret = printFileStat2(fname);
	//ret = printDirList(dir, fname5);
	//ret = printDirList2(dir, fname5);

	//sortingTest();

	//ret = printTime(ampm);
	//ret = printOpenFileError(fnameerr);

	searchingTest();

}
