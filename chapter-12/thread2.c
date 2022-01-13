#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
int run_now=1;
void *thread_function (void *arg);
int main(void)
{
	int print_count1=0;
	int res;
	void *thread_result;
	pthread_t a_thread;
	res=pthread_create(&a_thread,NULL,thread_function,NULL);
	if(res!=0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	while(print_count1++<20)
	{
		if(run_now==1)
		{
			printf("1");
			run_now=2;
		}
		else
			sleep(1);
	}
	printf("\nWaiting for thread to finish...\n");
	res=pthread_join(a_thread,NULL);
	if(res!=0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg)
{
	int print_count2=0;
	while(print_count2++<20)
	{
		if(run_now==2)
		{
			printf("2");
			run_now=1;
		}
		else
			sleep(1);
	}
//	pthread_exit(NULL);
}
