#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define BUFFERSIZE 1024

off_t CountFileSize(int iFile);

int main(int argc, char * argv[])
{
	int iCopyFile;
	int iPasteFile;
	char strBuffer[BUFFERSIZE] = {0};
	mode_t mtFileMode;
	int iOpenFlags;
	long long llFileSize;
	long long llCopySize;

	iOpenFlags = O_RDWR | O_CREAT;
	mtFileMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	if(argc < 3 || strcmp(argv[1],"--help") == 0)
	{
		usageErr("%s old-file new-file\n",argv[0]);
	}

	if((iCopyFile = open(argv[1],iOpenFlags, mtFileMode)) == -1)
	{
		errExit("open copy file");
	}
	if((iPasteFile = open(argv[2], iOpenFlags, mtFileMode)) == -1)
	{
		errExit("open paste file");
	}
	llFileSize = CountFileSize(iCopyFile);

	while(llFileSize > 0)
	{
		llCopySize = llFileSize > BUFFERSIZE ? BUFFERSIZE : llFileSize%BUFFERSIZE;			//caculate copy size(when file size < 1024 can copy rest data)
		llFileSize -= BUFFERSIZE;
		if(read(iCopyFile, strBuffer, llCopySize) == -1)
				errExit("read");
		if(write(iPasteFile, strBuffer, llCopySize) == -1)
				errExit("write");
	}


	return 0;
}

off_t CountFileSize(int iFile)
{
	off_t iFileSize;
	if((iFileSize = lseek(iFile, 0, SEEK_END)) == -1)
	{
		errExit("lseek");
	}
	if(lseek(iFile, 0, SEEK_SET) == -1)
	{
		errExit("lseek");
	}
	
	return iFileSize;
}
