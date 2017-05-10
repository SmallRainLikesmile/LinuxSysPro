#include <tlpi_hdr.h>

typedef struct memlog
{
	size_t stMemLenth;
	struct memlog * next;
	struct memlog * prev;
}MEMLOG, * PMEMLOG;

void * mymalloc(size_t stSize);
void myfree(void *ptr);
PMEMLOG getEnoughMem(size_t stSize);

PMEMLOG spIndex = NULL;

int main(int argc, char * argv[])
{
	int * iTest[20];
	int i;

	printf("One:%10p\n",sbrk(0));
	for(i = 0;i < 20;i ++)
	{
		iTest[i] = (int *)mymalloc(sizeof(int) * 10);
		if(iTest[i] == NULL)
		{
			printf("alloc have some question\n");
			exit(0);
		}
	}

	printf("Two:%10p\n",sbrk(0));
	for(i = 0;i < 20;i ++)
	{
		myfree(iTest[i]);
	}

	printf("Three:%10p\n",sbrk(0));
	exit(EXIT_SUCCESS);
}

void * mymalloc(size_t stSize)
{
	PMEMLOG spMemLog = NULL;
	void * llocMem = NULL;
	if((spMemLog = getEnoughMem(stSize)) == NULL)
	{
		llocMem = sbrk(stSize + sizeof(MEMLOG));
		spMemLog = (PMEMLOG)llocMem;
		spMemLog->stMemLenth = stSize;
		spMemLog->next = NULL;
		spMemLog->prev = NULL;
	}
	else
	{
		llocMem = (void *)spMemLog;
	}
	return llocMem + sizeof(MEMLOG);
}


PMEMLOG getEnoughMem(size_t stSize)
{
	PMEMLOG spMemLog = spIndex;
	void * ptIndex = NULL;
	if(spIndex == NULL)
			return NULL;
	do
	{
		if(spMemLog->stMemLenth < stSize)
			continue;
		else
		{
			if(spMemLog->stMemLenth == stSize || spMemLog->stMemLenth < stSize - sizeof(MEMLOG))
			{
				if(spMemLog->next == NULL && spMemLog->prev == NULL)
				{
					spIndex = NULL;
				}
				else if(spMemLog->next == NULL)
				{
					spIndex = spMemLog->prev;
					spIndex->next = NULL;
					spMemLog->prev = NULL;
					spMemLog->next = NULL;
				}
				else if(spMemLog->prev == NULL)
				{
					spMemLog->next->prev = NULL;
					spMemLog->next = NULL;
				}
				else
				{
					spMemLog->next->prev = spMemLog->prev;
					spMemLog->prev->next = spMemLog->next;
					spMemLog->next = NULL;
					spMemLog->prev = NULL;
				}
				return spMemLog;
			}
			else
			{
				ptIndex = (void *)spMemLog;
				PMEMLOG spMemInx = spMemLog;

				spMemLog = (PMEMLOG)(ptIndex + spMemInx->stMemLenth - stSize - sizeof(MEMLOG));
				spMemInx->stMemLenth -= sizeof(MEMLOG) + stSize;
				spMemLog->stMemLenth = stSize;
				spMemLog->next = NULL;
				spMemLog->prev = NULL;
				return spMemLog;
			}
		}
	}while((spMemLog = spMemLog->prev) == NULL);
	return NULL;
}

void myfree(void *ptr)
{
	PMEMLOG spMemLog = (PMEMLOG)(ptr - sizeof(MEMLOG));
	if(spIndex == NULL)
	{
		spIndex = spMemLog;
	}
	else
	{
		spIndex->next = spMemLog;
		spMemLog->prev = spIndex;
		spIndex = spMemLog;
	}
}
