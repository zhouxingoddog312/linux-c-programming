#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *thread_main(void *arg);
int main(void)
{
	pthread_t id;
	int thread_param=5;
	if(pthread_create(&id,NULL,thread_main,(void *)&thread_param)!=0)
	{
		puts("pthread_create() error!");
		exit(-1);
	}
//	sleep(10);
	sleep(2);
	puts("end of main!");
	exit(0);
}
void *thread_main(void *arg)
{
	int cnt=*(int *)arg;
	int i;
	for(i=0;i<cnt;i++)
	{
		sleep(1);
		puts("running thread.");
	}
	pthread_exit(NULL);
}
