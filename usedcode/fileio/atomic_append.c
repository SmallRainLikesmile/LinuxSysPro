#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"



int main(int argc, char * argv[])
{
	int iFile, iOpenFlags;
	mode_t mtOpenMode;
	char cWriteByte = 'x';
	long iWriteTimes = 0;

	iOpenFlags = O_WRONLY | O_CREAT;
	mtOpenMode = S_IRUSR | S_IWUSR;

	if(argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s file-name data-lenth file-mode\n",argv[1]);
	}

	if(argc == 3)
	{
		iOpenFlags |= O_APPEND;
	}

	iFile = open(argv[1], iOpenFlags, mtOpenMode);

	iWriteTimes = getLong(argv[2], GN_ANY_BASE, argv[2]);
	if(argc == 4)
	{
		while(iWriteTimes --)
		{
			lseek(iFile, 0, SEEK_END);
			write(iFile, &cWriteByte, 1);
		}
		printf("not append\n");
	}
	else
	{
		while(iWriteTimes --)
		{
			write(iFile, &cWriteByte, 1);
		}
		printf("append\n");
	}

	if(close(iFile) == -1)
			errExit("close");


	exit(EXIT_SUCCESS);
}
