#include <stdio.h>
#include <pthread.h>
int sum=0;
void *summation(void *arg);
int main(void)
{
	pthread_t t_id1,t_id2;
	int rang1[]={1,5};
	int rang2[]={6,10};
	pthread_create(&t_id1,NULL,summation,(void *)rang1);
	pthread_create(&t_id2,NULL,summation,(void *)rang2);
	pthread_join(t_id1,NULL);
	pthread_join(t_id2,NULL);
	printf("result: %d\n",sum);
	return 0;
}
void *summation(void *arg)
{
	int start=((int *)arg)[0];
	int end=((int *)arg)[1];
	while(start<=end)
	{
		sum+=start;
		start++;
	}
	pthread_exit(NULL);
}
