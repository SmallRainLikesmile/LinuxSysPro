#define _GNU_SOURCE

#include <stdlib.h>
#include "tlpi_hdr.h"



int main(int argc, char * argv[])
{
	int i;
	char ** pEnviron;

	clearenv();

	for(i = 0;i < argc;i ++)
	{
		if(putenv(argv[i]) != 0)
		{
			errExit("putenv: %s", argv[i]);
		}
	}

	if(setenv("GREET", "Hello world", 0) == -1)
	{
		errExit("setenv");
	}

	unsetenv("BYE");

	for(pEnviron = environ; *pEnviron != NULL; pEnviron ++)
	{
		puts(*pEnviron);
	}

	exit(EXIT_SUCCESS);
}
