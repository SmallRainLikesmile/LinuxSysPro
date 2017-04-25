#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"


int main(int argc, char * argv[])
{
	int iFile;

	File = open(atgv[1], O_WRONLY);

	if(File != -1)
	{
		printf("[PID %ld] File \"%s\" already exist)
	}

	return 0;
}
