#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
void *thread_main(void *arg);
int main(void)
{
	pthread_t t_id;
	int thread_param=5;
	void *retval;
	if(pthread_create(&t_id,NULL,thread_main,(void *)&thread_param)!=0)
	{
		puts("pthread_create() error!");
		exit(-1);
	}
	if(pthread_join(t_id,&retval)!=0)
	{
		puts("pthread_wait() error!");
		exit(-1);
	}
	printf("Thread return message: %s\n",(char *)retval);
	free(retval);
	exit(0);
}
void *thread_main(void *arg)
{
	int cnt=*(int *)arg;
	int i;
	char *msg=malloc(sizeof(char)*50);
	strcpy(msg,"Hello, I am thread~");
	for(i=0;i<cnt;i++)
	{
		sleep(1);
		puts("running thread");
	}
	pthread_exit((void *)msg);
}
