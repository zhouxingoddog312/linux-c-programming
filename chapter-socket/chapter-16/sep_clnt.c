#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int sock;
	FILE *readfp,*writefp;
	char message[BUF_SIZE]={0,};
	int str_len;
	struct sockaddr_in serv_addr;
	if(argc!=3)
	{
		printf("Usage : %s <IP> <port>\n",argv[0]);
		exit(1);
	}
	sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock==-1)
		error_handling("socket() error!");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	inet_aton(argv[1],&serv_addr.sin_addr);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error!");
	else
		printf("Connected......");
	readfp=fdopen(sock,"r");
	writefp=fdopen(sock,"w");
	while(1)
	{
		if(fgets(message,BUF_SIZE,readfp)==NULL)
			break;
		fputs(message,stdout);
		fflush(stdout);
	}
	fputs("From client: Thank you!",writefp);
	fflush(writefp);
	fclose(writefp);
	fclose(readfp);
	exit(0);
}
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
