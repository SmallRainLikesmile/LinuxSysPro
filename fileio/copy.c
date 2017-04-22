#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <tlpi_hdr.h>
#include <error_functions.h>

#define BUFFERSIZE 1024

int main(int argc, char * argv[])
{
	int InfactSize;

	if(argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s old-file new-file\n",argv[0]);
	}

	int File = open(argv[1],O_RDONLY);
	if(File == -1)
	{
		errExit("opening file %s\n",argv[1]);
	}

	char * Buffer = (char *)malloc(BUFFERSIZE);
	int FileFlags = O_CREAT | O_WRONLY | O_TRUNC;
	mode_t FileMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int NewFile = open(argv[2], FileFlags, FileMode);
	if(NewFile == -1)
	{
		errExit("opening file %s\n",argv[2]);
	}

	printf("START\n");
	while((InfactSize = read(File, Buffer, BUFFERSIZE)) > 0)
	{
		if(InfactSize < BUFFERSIZE)
		{
			*(Buffer + InfactSize) = '\0';
		}
		if(write(NewFile, Buffer, InfactSize) != InfactSize)
		{
			fatal("Couldn't write whole buffer");
		}
		if(InfactSize == -1)
		{
			errExit("read");
		}
	}
	printf("copy over\nEND\n");

	if(close(File) == -1)
	{
		errExit("close input");
	}
	if(close(NewFile) == -1)
	{
		errExit("close output");
	}
	free(Buffer);
	return 0;
}
