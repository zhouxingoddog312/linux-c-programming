#include <stdio.h>
#include <pthread.h>
#define THREAD_NUM 100
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *thread_inc(void *arg);
void *thread_des(void *arg);
long long num=0;
int main(void)
{
	pthread_t t_id[THREAD_NUM];
	int i;
	printf("sizeof long long: %d\n",sizeof(long long));
	for(i=0;i<THREAD_NUM;i++)
	{
		if(i%2==0)
			pthread_create(&t_id[i],NULL,thread_inc,NULL);
		else
			pthread_create(&t_id[i],NULL,thread_des,NULL);
	}
	for(i=0;i<THREAD_NUM;i++)
		pthread_join(t_id[i],NULL);
	printf("result: %lld\n",num);
	pthread_mutex_destroy(&mutex);
	return 0;
}
void *thread_inc(void *arg)
{
	for(int i=0;i<50000000;i++)
	{
		pthread_mutex_lock(&mutex);
		num+=1;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}
void *thread_des(void *arg)
{
	pthread_mutex_lock(&mutex);
	for(int i=0;i<50000000;i++)
		num-=1;
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}
