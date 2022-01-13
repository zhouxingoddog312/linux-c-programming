#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define WORK_SIZE 1024

sem_t bin_sem;
void *thread_function(void *arg);
char work_area[WORK_SIZE];
int main(void)
{
	int res;
	pthread_t a_thread;
	void *thread_result;
	res=sem_init(&bin_sem,0,0);
	if(res!=0)
	{
		perror("Semphore initialization failed");
		exit(EXIT_FAILURE);
	}
	res=pthread_create(&a_thread,NULL,thread_function,NULL);
	if(res!=0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Input some text. Enter 'end' to finish\n");
	while(strncmp("end",work_area,3)!=0)
	{
		if(strncmp("FAST",work_area,4)==0)
		{
			//puts("1");
			sem_post(&bin_sem);
			strcpy(work_area,"Wheeee...");
		}
		else
			fgets(work_area,WORK_SIZE,stdin);
		//puts("2");
		sem_post(&bin_sem);
	}
	printf("\nWaiting for thread to finish...\n");
	res=pthread_join(a_thread,&thread_result);
	if(res!=0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	sem_destroy(&bin_sem);
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg)
{
	sem_wait(&bin_sem);
	while(strncmp("end",work_area,3)!=0)
	{
		printf("You input %ld characters\n",strlen(work_area)-1);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}
