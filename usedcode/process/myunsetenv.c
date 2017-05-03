#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include "tlpi_hdr.h"

extern char ** environ;

int myunsetenv(char * name);

int main(int argc, char * argv[])
{
	putenv("test=one:two");

	char ** p;

	myunsetenv("test");

	for(p=environ; *p != NULL; p ++)
	{
		puts(*p);
	}

	exit(EXIT_SUCCESS);
}
int myunsetenv( char * name)
{
	if(name == NULL)
	{
		return -1;
	}

	if(putenv(name) != 0)
	{
		return -1;
	}
	return 0;
}
