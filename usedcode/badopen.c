#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"


int main(int argc, char * argv[])
{
	int iFile;

	iFile = open(argv[1], O_WRONLY);

	if(iFile != -1)
	{
		printf("[PID %ld] iFile g \"%s\" already exist\n", (long) getpid(), argv[1]);
	}
	else 
	{
		if(errno != ENOENT)
		{
			errExit("open");
		}
		else
		{
			printf("[PID %ld] File \"%s\" doesn't exist yet\n",(long)getpid(), argv[1]);
			if(argc > 2)
			{
				sleep(5);
				printf("[PID %ld] Done sleeping\n",(long)getpid());
			}

			iFile = open(argv[1], O_CREAT|O_WRONLY, S_IRUSR | S_IWUSR);

			if(iFile == -1)
			{
				errExit("open");
			}
			printf("[PID %ld] Create file \"%s\" exclusively\n", (long) getpid(), argv[1]);
		}
	}
	return 0;
}
