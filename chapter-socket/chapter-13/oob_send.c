#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int sock;
	struct sockaddr_in sock_addr;
	if(argc!=3)
	{
		fprintf(stderr,"Usage : %s <IP> <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock==-1)
		error_handling("socket() error!");
	memset(&sock_addr,0,sizeof(sock_addr));
	sock_addr.sin_family=AF_INET;
	inet_aton(argv[1],&sock_addr.sin_addr);
	sock_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock,(struct sockaddr *)&sock_addr,sizeof(sock_addr))==-1)
		error_handling("connect() error!");
	write(sock,"123",strlen("123"));
	send(sock,"4",strlen("4"),MSG_OOB);
	write(sock,"567",strlen("567"));
	send(sock,"890",strlen("890"),MSG_OOB);
	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
