#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include "tlpi_hdr.h"

#ifndef BUFFERSIZE
#define BUFFERSIZE 1024
#endif

static int StaFile;

/********************************
 *
 * signal capture (after getting ctrl+c - close file)
 *
 * *****************************/

void Stop(int Signo)
{
	if(close(StaFile) == -1)
	{
		errExit("Close output file");
	}
	printf("%d\n",Signo);
	exit(0);
}

int main(int argc, char * argv[])
{
	int File;				//file descriptor
	char Buffer[BUFFERSIZE];	//input buffer
	int ReadRealSize;			//input real size
	int OpenFlags;				//file access mode
	char * FileName = NULL;		//file name

	signal(SIGINT, Stop);		//capture signal

	mode_t FileMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; //file access

	if(argc < 2||strcmp(argv[1],"--help") == 0)
	{
		usageErr("%s save file\n",argv[0]);
	}

	OpenFlags = O_WRONLY;

	//deal with input parameter
	FileName = argv[1];
	if(argc == 3)
	{
		FileName = argv[2];
		if(strcmp(argv[1], "-a") == 0)
		{
				printf("Get it\n");
			OpenFlags |= O_APPEND;
		}
		else
		{
			OpenFlags |= O_CREAT | O_TRUNC;
		}
	}

	File = open(FileName,OpenFlags, FileMode);
	StaFile = File;
	if(File == -1)
	{
		errExit("opening file %s", argv[1]);
	}

	//get input data , and output to stdio and specified file
	while((scanf("%s",Buffer)) != 0)
	{
		ReadRealSize = strlen(Buffer) + 1;
		Buffer[ReadRealSize-1] = '\n';
		Buffer[ReadRealSize] = '\0';
		if(write(File, Buffer, ReadRealSize) != ReadRealSize)
		{
			fatal("Couldn't write whole buffer");
		}
		printf("%s",Buffer);
	}
	printf("Over\n");


	if(close(File) == -1)
	{
		errExit("Close output file");
	}
	return 0;
}
