#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define A_MEGABYTE (1024*1024)
#define PHY_MEM_MEGS (1024*16)
int main(void)
{
	char *some_memory;
	size_t size_to_allocate=A_MEGABYTE;
	int megs_obtained=0;
	while(megs_obtained<(2*PHY_MEM_MEGS))
	{
		some_memory=(char *)malloc(size_to_allocate);
		if(some_memory)
		{
			megs_obtained++;
			sprintf(some_memory,"Hello World");
			printf("%s - Now allocated %d Megabytes\n",some_memory,megs_obtained);
		}
		else
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
