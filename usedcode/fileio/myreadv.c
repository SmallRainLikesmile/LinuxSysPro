#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include "tlpi_hdr.h"

int myreadv(int iFile, const struct iovec * iov, int iovcnt);

int main(int argc, char * argv[])
{
	int iFile, iFileFlags;
	mode_t mtFileMode;
	struct iovec iov[3];
	char x,y,z;

	iov[0].iov_base = &x;
	iov[0].iov_len = sizeof(x);
	iov[1].iov_base = &y;
	iov[1].iov_len = sizeof(y);
	iov[2].iov_base = &z;
	iov[2].iov_len = sizeof(z);


	iFileFlags = O_RDWR | O_CREAT;

	mtFileMode = S_IRUSR | S_IWUSR;

	if(argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s file-name\n",argv[0]);
	}

	if((iFile = open(argv[1], iFileFlags, mtFileMode)) == -1)
	{
		errExit("open");
	}

	myreadv(iFile, iov, 3);

	printf("%c %c %c\n",x,y,z);

	if(close(iFile) == -1)
	{
		errExit("close");
	}
	exit(EXIT_SUCCESS);
}
int myreadv(int iFile, const struct iovec * iov, int iovcnt)
{
	int iRet = 0;
	while(iovcnt --)
	{
		if(read(iFile, iov->iov_base, iov->iov_len) == -1)
		{
			errExit("read %d",iovcnt);
		}
		iRet += iov->iov_len;
		iov ++;
	}
	return iRet;
}
