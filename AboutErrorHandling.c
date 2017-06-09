#include "Common.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

 
int printOpenFileError(char *fname)
{
   //char fname[20] = "testnofile.txt";
   int  fhndl;
   /* try to open non-existing file */
   if((fhndl = _open(fname, _O_RDONLY)) == -1)
   {
      /* using the possible ways to create error message */
      perror("Using perror()");
      printf("Using strerror(): %s\n", strerror(errno));
      printf(_strerror("_strerror()"));
      printf("There is some error opening %s file\n", fname);
   }
   else
   {
      printf("Open %s for reading succeeded!\n", fname);
      _close(fhndl);
   }
   return 0;
}
