#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main(void)
{
	int sock;
	sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	pid_t pid=fork();
	if(pid==0)
		printf("sock : %d\n",sock);
	else
		printf("sock : %d\n",sock);
	close(sock);
	return 0;
}
