#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 50
int main(void)
{
	int fds1[2],fds2[2];
	pid_t pid;
	char buf[BUF_SIZE];
	char str1[]="Who are you?";
	char str2[]="Thank you for your message.";
	pipe(fds1);
	pipe(fds2);
	pid=fork();
	if(pid==0)
	{
		close(fds1[0]);
		close(fds2[1]);
		write(fds1[1],str1,sizeof(str1));
		read(fds2[0],buf,BUF_SIZE);
		printf("Child process output: %s\n",buf);
	}
	else
	{
		close(fds1[1]);
		close(fds2[0]);
		write(fds2[1],str2,sizeof(str2));
		read(fds1[0],buf,BUF_SIZE);
		printf("Parent process output: %s\n",buf);
	}
	return 0;
}
