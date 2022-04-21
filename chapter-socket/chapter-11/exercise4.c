#include <unistd.h>
#include <stdio.h>
#define BUF_SIZE 50
int main(void)
{
	int fds1[2],fds2[2];
	pid_t pid;
	pipe(fds1);
	pipe(fds2);
	pid=fork();
	if(pid==0)
	{
		int result;
		close(fds1[0]);
		close(fds2[1]);
		int i=0,index;
		for(index=0;index<3;i++,index++)
		{
			write(fds1[1],&i,sizeof(i));
			read(fds2[0],&result,sizeof(result));
			printf("Child proc : %d\n",result);
		}
	}
	else
	{
		int result;
		close(fds1[1]);
		close(fds2[0]);
		int i=0,index;
		for(index=0;index<3;i++,index++)
		{
			write(fds2[1],&i,sizeof(i));
			read(fds1[0],&result,sizeof(result));
			printf("Parent proc : %d\n",result);
		}
	}
	return 0;
}
