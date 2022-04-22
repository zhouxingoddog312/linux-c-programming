#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#define BUF_SIZE 50
int main(void)
{
	fd_set reads,temps;
	int result,strlen;
	char buf[BUF_SIZE];
	struct timeval timeout;
	FD_ZERO(&reads);
	FD_SET(0,&reads);
	while(1)
	{
		temps=reads;
		timeout.tv_sec=5;
		timeout.tv_usec=100;
		result=select(1,&temps,0,0,&timeout);
		if(result==-1)
		{
			puts("select() error!");
			break;
		}
		else if(result==0)
			puts("timeout!");
		else
		{
			if(FD_ISSET(0,&temps))
			{
				strlen=read(0,buf,BUF_SIZE);
				buf[strlen]='\0';
				printf("message from consle: %s",buf);
			}
		}
	}
	return 0;
}
