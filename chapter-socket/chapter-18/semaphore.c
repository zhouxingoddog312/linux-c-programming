#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
void *read(void *arg);
void *accu(void *arg);
static sem_t sem_one;
static sem_t sem_two;
static int num=0;
int main(void)
{
	pthread_t t_id1,t_id2;
	sem_init(&sem_one,0,0);
	sem_init(&sem_two,0,1);
	pthread_create(&t_id1,NULL,read,NULL);
	pthread_create(&t_id2,NULL,accu,NULL);
	pthread_join(t_id1,NULL);
	pthread_join(t_id2,NULL);
	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}
void *read(void *arg)
{
	int i;
	for(i=0;i<5;i++)
	{
		fputs("Input num: ",stdout);
		sem_wait(&sem_two);
		scanf("%d",&num);
		sem_post(&sem_one);
	}
	pthread_exit(NULL);
}
void *accu(void *arg)
{
	int i,sum=0;
	for(i=0;i<5;i++)
	{
		sem_wait(&sem_one);
		sum+=num;
		sem_post(&sem_two);
	}
	printf("Result: %d\n",sum);
	pthread_exit(NULL);
}
