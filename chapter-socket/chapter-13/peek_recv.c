#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 100
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int recv_sock;
	int acpt_sock;
	struct sockaddr_in acpt_addr,recv_addr;
	socklen_t recv_addr_sz;
	int str_len;
	char buf[BUF_SIZE];
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	acpt_sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(acpt_sock==-1)
		error_handling("socket() error!");
	memset(&acpt_addr,0,sizeof(acpt_addr));
	acpt_addr.sin_family=AF_INET;
	acpt_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	acpt_addr.sin_port=htons(atoi(argv[1]));
	if(bind(acpt_sock,(struct sockaddr *)&acpt_addr,sizeof(acpt_addr))==-1)
		error_handling("bind() error!");
	if(listen(acpt_sock,5)==-1)
		error_handling("listen() error!");
	recv_addr_sz=sizeof(recv_addr);
	recv_sock=accept(acpt_sock,(struct sockaddr *)&recv_addr,&recv_addr_sz);
	while(1)
	{
		str_len=recv(recv_sock,buf,BUF_SIZE-1,MSG_PEEK|MSG_DONTWAIT);
		if(str_len>0)
			break;
	}
	buf[str_len]='\0';
	printf("Buffering %d bytes: %s\n",str_len,buf);
	str_len=recv(recv_sock,buf,BUF_SIZE-1,0);
	buf[str_len]='\0';
	printf("Read again: %s\n",buf);
	close(recv_sock);
	close(acpt_sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
