#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int main(int argc, char * argv[])
{
	int iFile, iNewFile, iFileFlags;
	mode_t mtFileMode;
	char cInputC = 'C';
	char cInputB = 'B';
	int iNewFlags;

	iFileFlags = O_WRONLY | O_CREAT;

	mtFileMode = S_IRUSR | S_IWUSR;

	if(argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s file-name\n",argv[0]);
	}

	if((iFile = open(argv[1], iFileFlags, mtFileMode)) == -1)
	{
		errExit("open");
	}

	iNewFile = dup(iFile);
printf("%d %d \n",iFile, iNewFile);
	iNewFlags = fcntl(iFile, F_GETFL);

	if(iNewFlags & O_WRONLY)
	{
		printf("share file descriptor\n");
	}
	else
	{
		printf("don't share descriptor\n");
	}

	lseek(iFile, 50, SEEK_SET);
	write(iNewFile, &cInputC, 1);

	lseek(iNewFile, 60, SEEK_SET);
	write(iFile, &cInputB, 1);

	if(close(iNewFile) == -1)
	{
		errExit("close1");
	}
	if(close(iFile) == -1)
	{
		errExit("close2");
	}

	exit(EXIT_SUCCESS);
}
