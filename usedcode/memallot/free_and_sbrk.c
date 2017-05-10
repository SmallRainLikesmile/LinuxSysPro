#include "tlpi_hdr.h"

#define MAX_ALLOCS 1000000

int main(int argc, char * argv[])
{
	char * ptr[MAX_ALLOCS];
	int iFreeStep, iFreeMin, iFreeMax, iBlockSize, iNumAllocs, j;

//	printf("\n");

	if(argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s num-allocs block-size [step[min[max]]]\n", argv[0]);
	}

	iNumAllocs = getInt(argv[1], GN_GT_O, "num-allocs");
	if(iNumAllocs > MAX_ALLOCS)
	{
		cmdLineErr("num-allocs > %d\n", MAX_ALLOCS);
	}

	iBlockSize = getInt(argv[2], GN_GT_O|GN_ANY_BASE, "block-size");

	iFreeStep = (argc > 3) ? getInt(argv[3], GN_GT_O, "step") : 1;
	iFreeMin = (argc > 4) ? getInt(argv[4], GN_GT_O, "min") : 1;
	iFreeMax = (argc > 5) ? getInt(argv[5], GN_GT_O, "max") : iNumAllocs;
	printf("%d %d %d\n\n",iFreeStep, iFreeMin, iFreeMax);	
	if(iFreeMax > iNumAllocs)
	{
		cmdLineErr("iFreeMax > iNumAllocs\n");
	}

	printf("Initial program break:   %10p\n",sbrk(0));

	printf("Allocing %d*%d bytes",iBlockSize, iNumAllocs);

	for(j = 0;j < iNumAllocs;j ++)
	{
		ptr[j] = malloc(iBlockSize);
		if(ptr[j] == NULL)
		{
			errExit("malloc");
		}
	}

	printf("After malloc program break:   %10p\n",sbrk(0));

	printf("freeing blocks from %d to %d in steps of %d\n",iFreeMin, iFreeMax, iFreeStep);
	for(j = iFreeMin - 1;j < iFreeMax; j += iFreeStep)
	{
		free(ptr[j]);
	}

	printf("after free,program break is:   %10p\n",sbrk(0));


	exit(EXIT_SUCCESS);
}
