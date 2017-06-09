#include "Common.h"


// buffer, be careful with terminated NULL. Must match with ++mydrives[1]...that is one space
// for example if no one space: "A:"--> ++mydrives[0];
// you may try char mydrives[ ] = {" A: "}; or char mydrives[ ] = " A: ";
TCHAR mydrives[] = " A: ";

int printLogicalDrive() {
	// get the drives bit masks...1 is available, 0 is not available A = least significant bit...
	ULONG DriveMask = _getdrives();
	// if something wrong
	if (DriveMask == 0)
		printf("_getdrives() failed with failure code: %d\n", GetLastError());
	else {
		printf("This machine has the following logical drives:\n");
		while (DriveMask) {   // list all the drives...
			if (DriveMask & 1)
				printf(mydrives);
			// go to the next drive strings with one space
			++mydrives[1];
			// shift the bit masks binary to the right and repeat
			DriveMask >>= 1;
		}
		printf("\n");
	}
	return 0;
}
