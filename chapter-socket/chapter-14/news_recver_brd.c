#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 100
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int recv_sock;
	struct sockaddr_in recv_addr;
	int str_len;
	char buf[BUF_SIZE];
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	recv_sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	memset(&recv_addr,0,sizeof(recv_addr));
	recv_addr.sin_family=AF_INET;
	recv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	recv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(recv_sock,(struct sockaddr *)&recv_addr,sizeof(recv_addr))==-1)
		error_handling("bind() error!");
	while(1)
	{
		str_len=recvfrom(recv_sock,buf,BUF_SIZE-1,0,NULL,0);
		if(str_len<0)
			break;
		buf[str_len]='\0';
		fputs(buf,stdout);
	}
	close(recv_sock);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
