#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
int flag=0;
void ctrlc(int sig)
{
	char ch;
	if(sig==SIGINT)
	{
		fputs("是否确定退出程序：",stdout);
		ch=getchar();
		if(ch=='y'||ch=='Y')
			flag=1;
		else
			;
	}
}
int main(void)
{
	struct sigaction act;
	act.sa_flags=0;
	sigemptyset(&act.sa_mask);
	act.sa_handler=ctrlc;
	sigaction(SIGINT,&act,0);
	while(!flag)
	{
		puts("continue...");
		sleep(2);
	}
	return 0;
}
