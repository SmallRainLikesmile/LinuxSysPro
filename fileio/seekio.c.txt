#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include "tlpi_hdr.h"

int main(int argc,char * argv[])
{
	int iFile;
	int iOpenFlags;
	mode_t mtFileMode;
	size_t stLen;
	char * strBuffer = NULL;
	off_t otOffset;
	int iCmdNum;
	int iReadSize;
	int i;
	int iWriteSize;

	if(argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		errExit("%s file {r<length>|R<Rlength>|w<string>|s<offset>} ...\n",argv[0]);
	}

	iOpenFlags = O_RDWR | O_CREAT;
	mtFileMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	iFile = open(argv[1], iOpenFlags, mtFileMode);

	if(iFile == -1)
	{
		errExit("opening file %s",argv[1]);
	}

	for(iCmdNum = 2; iCmdNum < argc; iCmdNum ++)
	{
		switch(argv[iCmdNum][0])
		{
			case 'r':
			case 'R':
				{
					stLen = getLong(&argv[iCmdNum][1], GN_ANY_BASE, argv[iCmdNum]);
					strBuffer = (char *)malloc(stLen);
					if(strBuffer == NULL)
					{
						errExit("malloc failed");
					}
					if((iReadSize = read(iFile, strBuffer, stLen)) == -1)
					{
						errExit("read failed");
					}
					if(iReadSize == 0)
					{
						printf("%s: end of file\n", argv[iCmdNum]);
					}
					else
					{
						printf("%s:",argv[iCmdNum]);
						for(i = 0;i < iReadSize;i ++)
						{
							if(argv[iCmdNum][0] == 'r')
							{
								printf("%c",isprint((unsigned char)strBuffer[i]) ? strBuffer[i] : '?');
							}
							else
							{
								printf("%02x ", (unsigned int)strBuffer[i]);
							}
						}
						printf("\n");
					}
					free(strBuffer);
				}break;
			case 's':
				{
					otOffset = getLong(&argv[iCmdNum][1], GN_ANY_BASE, argv[iCmdNum]);
					if(lseek(iFile, otOffset, SEEK_SET) == -1)
					{
						errExit("lseek");
					}
					printf("%s:seek is succeeded\n",argv[iCmdNum]);
				}break;
			case 'w':
				{
					iWriteSize = write(iFile, &argv[iCmdNum][1], strlen(&argv[iCmdNum][1]));
					if(iWriteSize == -1)
					{
						errExit("write");
					}
					printf("%s wrote %d\n",argv[iCmdNum],iWriteSize);
				}break;

			default:
				cmdLineErr("Argument must start with [wrRs] %s",argv[iCmdNum]);
		}
	}

	return 0;
}
