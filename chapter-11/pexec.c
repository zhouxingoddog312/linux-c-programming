#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char * const ps_argv[]={"ps","ax",0};
	char * const ps_envp[]={"PATH=/bin:/usr/bin","TERM=xterm-256color",0};
	printf("Running ps with execlp\n");

//	execlp("ps","ps","ax",0);

//	execl("/bin/ps","ps","ax",0);
//	execle("/bin/ps","ps","ax",0,ps_envp);
//	execv("/bin/ps",ps_argv);
//	execvp("ps",ps_argv);
	execve("/bin/ps",ps_argv,ps_envp);

	printf("Done!\n");
	exit(0);
}
