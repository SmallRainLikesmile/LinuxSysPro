#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include "tlpi_hdr.h"

int mywrite(int iFile, const struct iovec * iov, int iovcnt);

int main(int argc, char * argv[])
{
	int iFile, iFileFlags;
	mode_t mtFileMode;
	struct iovec iov[3];
	char * x = "hello";
	char * y = "beautiful";
	char * z = "world";

	iFileFlags = O_RDWR | O_CREAT;
	mtFileMode = S_IRUSR | S_IWUSR;

	if(argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s file-name\n",argv[1]);
	}

	if((iFile = open(argv[1], iFileFlags, mtFileMode)) == -1)
	{
		errExit("open");
	}

	iov[0].iov_base = x;
	iov[0].iov_len = strlen(x);
	iov[1].iov_base = y;
	iov[1].iov_len = strlen(y);
	iov[2].iov_base = z;
	iov[2].iov_len = strlen(z);

	mywrite(iFile, iov, 3);

	exit(EXIT_SUCCESS);
}
int mywrite(int iFile, const struct iovec * iov, int iovcnt)
{
	int iRet = 0;

	while(iovcnt --)
	{
		if(write(iFile, iov->iov_base, iov->iov_len) == -1)
		{
			errExit("write");
		}
		iRet += iov->iov_len;
		iov ++;
	}
	return iRet;
}
