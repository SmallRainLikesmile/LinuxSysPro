#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"



int main(int argc, char * argv[])
{
	int iFile, iOpenFlags;
	mode_t mtOpenMode;

	iOpenFlags = O_WRONLY | O_APPEND;
	mtOpenMode = S_IRUSR | S_IWUSR;

	if(argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s openfile wirte-data\n",argv[1]);
	}

	iFile = open(argv[1], iOpenFlags, mtOpenMode);
	//If  the  file was open(2)ed with O_APPEND, the file offset is first set
	//       to the end of the file before writing. 
	//       so lseek to set offset to the start is useless
	if(lseek(iFile, 0, SEEK_SET) == -1)
			errExit("lseek");
	if(write(iFile, argv[2], strlen(argv[2])) == -1)
			errExit("write");

	if(close(iFile) == -1)
			errExit("close");


	exit(EXIT_SUCCESS);
}
