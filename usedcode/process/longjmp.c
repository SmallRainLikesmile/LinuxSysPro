#include <setjmp.h>
#include "tlpi_hdr.h"


static jmp_buf env;

static void func2(void)
{
	printf("func2\n");
	longjmp(env,2);
}

static void func1(int argc)
{
	if(argc == 1)
			longjmp(env, 1);
	func2();
}

int main(int argc, char * argv[])
{
	switch(setjmp(env))
	{
		case 0:
			printf("Calling func1() after the initial setjmp()\n");
			func1(argc);
			break;
		case 1:
			printf("Jumped from func1()\n");
			break;
		case 2:
			printf("Jummped from func2()\n");
			break;
	}
	exit(EXIT_SUCCESS);
}
