#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int sock;
	int rcv_buf=3*1024,snd_buf=3*1024;
	socklen_t len;
	int state;
	sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	state=setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void *)&snd_buf,sizeof(snd_buf));
	if(state)
		error_handling("setsockopt() error");
	state=setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void *)&rcv_buf,sizeof(rcv_buf));
	if(state)
		error_handling("setsockopt() error");
	len=sizeof(rcv_buf);
	state=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void *)&rcv_buf,&len);
	if(state)
		error_handling("getsockopt() error");
	len=sizeof(snd_buf);
	state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void *)&snd_buf,&len);
	if(state)
		error_handling("getsockopt() error");
	printf("Input buffer size %d\n",rcv_buf);
	printf("Output buffer size %d\n",snd_buf);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
