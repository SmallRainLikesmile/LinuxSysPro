#include <tlpi_hdr.h>

extern char ** environ;

int main(int argc, char * argv[], char * envp[])
{
	char ** ep;

	for(ep = environ; ep != NULL; ep ++)
	{
		puts(*ep);
	}

	for(; *envp != NULL; envp++)
			puts(*envp);

	exit(EXIT_SUCCESS);
}
