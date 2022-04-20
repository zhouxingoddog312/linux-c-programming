#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 50
void error_handling(char *message);
void write_routine(int sock,char *buf);
void read_routine(int sock,char *buf);
int main(int argc,char *argv[])
{
	int sock;
	struct sockaddr_in sock_addr;
	pid_t pid;
	char buf[BUF_SIZE];
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
	pid=fork();
	if(pid==0)
		write_routine(sock,buf);
	else
		read_routine(sock,buf);
	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
void write_routine(int sock,char *buf)
{
	while(1)
	{
		fgets(buf,BUF_SIZE,stdin);
		if(!strcmp(buf,"q\n")||!strcmp(buf,"Q\n"))
		{
			shutdown(sock,SHUT_WR);
			return;
		}
		write(sock,buf,strlen(buf));
	}
}
void read_routine(int sock,char *buf)
{
	while(1)
	{
		int str_len=read(sock,buf,BUF_SIZE);
		if(str_len==0)
			return;
		buf[str_len]='\0';
		printf("Message from server: %s",buf);
	}
}
