#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
void ctrlc(int sig)
{
	if(sig==SIGALRM)
	{
		fputs("1秒后继续输出\n",stdout);
		alarm(1);
	}
}
int main(void)
{
	struct sigaction act;
	act.sa_flags=0;
	sigemptyset(&act.sa_mask);
	act.sa_handler=ctrlc;
	sigaction(SIGALRM,&act,0);
	alarm(1);
	while(1)
		sleep(10);
	return 0;
}
