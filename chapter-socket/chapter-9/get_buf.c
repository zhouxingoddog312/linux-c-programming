#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int sock;
	socklen_t len;
	int rcv_buf,snd_buf;
	int state;
	sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	len=sizeof(rcv_buf);
	state=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void *)&rcv_buf,&len);
	if(state)
		error_handling("getsockopt() error!");
	len=sizeof(snd_buf);
	state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void *)&snd_buf,&len);
	if(state)
		error_handling("getsockopt() error!");
	printf("Input buffer %d\n",rcv_buf);
	printf("Output buffer %d\n",snd_buf);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
