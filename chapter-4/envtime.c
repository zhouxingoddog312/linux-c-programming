#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(void)
{
	time_t the_time;
	for(int i=1;i<=10;i++)
	{
		the_time=time((time_t *)0);
		printf("The time is %ld\n",the_time);
		sleep(1);
	}
	exit(0);
}
