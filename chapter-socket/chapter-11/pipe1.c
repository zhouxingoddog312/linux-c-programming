#include <unistd.h>
#include <stdio.h>
#define BUF_SIZE 50
int main(void)
{
	int fds[2],len;
	pid_t pid;
	char buf[BUF_SIZE];
	char str[]="Who are you?";
	pipe(fds);
	pid=fork();
	if(pid==0)
	{
		write(fds[1],str,sizeof(str));
	}
	else
	{
		len=read(fds[0],buf,BUF_SIZE);
		printf("%s\n",buf);
	}
	return 0;
}
