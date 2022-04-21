#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 50
int main(void)
{
	char str1[]="Who are you?";
	char str2[]="Thank you for your message.";
	int fds[2];
	char buf[BUF_SIZE];
	pid_t pid;
	pipe(fds);
	pid=fork();
	if(pid==0)
	{
		write(fds[1],str1,sizeof(str1));
		//sleep(2);
		read(fds[0],buf,BUF_SIZE);
		printf("Child process output: %s\n",buf);
	}
	else
	{
		read(fds[0],buf,BUF_SIZE);
		printf("Parent process output: %s\n",buf);
		write(fds[1],str2,sizeof(str2));
		sleep(3);
	}
	return 0;
}
