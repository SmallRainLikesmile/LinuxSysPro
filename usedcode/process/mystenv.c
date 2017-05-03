#define _GNU_SOURC
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tlpi_hdr.h"

extern char ** environ;

int mysetenv(const char * name, const char * value, int overwrite);

void test(void)
{
	putenv("test=two");
	mysetenv("test", "one", 1);
	printf("%s\n",getenv("test"));
}

int main(int argc, char * argv[])
{
	test();
	exit(EXIT_SUCCESS);
}


int mysetenv(const char * name, const char * value, int overwrite)
{
	char * strBuf = NULL;
	size_t stStrSize = 0;

	stStrSize = strlen(name) + strlen(value);

	strBuf = (char *)malloc(stStrSize + 1);

	if(strBuf == NULL)
	{
		return -1;
	}

	strcat(strBuf, name);
	strcat(strBuf, "=");
	strcat(strBuf, value);

	if(overwrite == 0 && getenv(name) != 0)
	{}
	else
	{
		putenv(strBuf);
	}

	free(strBuf);
	return 0;
}
