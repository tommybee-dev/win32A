#ifndef __COMMON_H__
#define __COMMON_H__

#include <windows.h>
#include <direct.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#ifdef __cplusplus
extern "C" {
#endif



int printLogicalDrive();
int printLocalSpaces();
int testDirectory(void);
int checkDirectory(void);
int printFileAttr(const char *path);
int changFileSize(const char *fname);
int changFileSize2(const char *fname);
void DisplayFullPath(char *relPath);
int printMakeSplitPath(const char *driveLetter, const char *path, const char *fileName, const char* fileExt);
int accessAndRemoveFile(char *obj, char *newObj);
int createMaskAndOpenFile(char *fineName);
int createMaskAndOpenFile2(char *fineName);
int printFileStat(char *fileName);
int printFileStat2(char *fileName);
int printDirList(char *dir, char *fname) ;
int printDirList2(char *dir, char *fname) ;


int SortingTest(int argc, char *argv[], char *key);
int printTime(char *ampm);
int printOpenFileError(char *fname);



#ifdef __cplusplus
};
#endif

int SearchTest(int argc, char *argv[], TCHAR *driv) ;

#endif
