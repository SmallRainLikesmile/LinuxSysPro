#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int mydup2(int iOldfd, int iNewfd);

int main(int argc, char * argv[])
{
	int iFile, iFileFlags, iNewFile;
	mode_t mtFileMode;

	iFileFlags = O_WRONLY | O_CREAT;

	mtFileMode = S_IRUSR | S_IWUSR;

	if(argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("[%s] filename\n",argv[0]);
	}

	if((iFile = open(argv[1], iFileFlags, mtFileMode)) == -1)
	{
		errExit("open");
	}
	
	iNewFile = dup2(iFile, 7);
	//iNewFile = mydup2(iFile,7);

	printf("oldFile descriptor %d\nnewFile descriptor %d\n",iFile, iNewFile);

	if(close(iFile) == -1)
	{
		errExit("close");
	}
	exit(EXIT_SUCCESS);
}
int mydup2(int iOldfd, int iNewfd)
{
	if(iOldfd == iNewfd)
	{
		if(fcntl(iOldfd, F_GETFL) == -1)
		{
			errno = EBADF;
			return -1;
		}
		else
		{
			return iOldfd;
		}
	}

	close(iNewfd);

	return fcntl(iOldfd, F_DUPFD, iNewfd);

}
