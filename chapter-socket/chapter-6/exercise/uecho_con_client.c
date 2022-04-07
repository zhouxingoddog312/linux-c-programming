#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 50
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int count=0;
	int sock;
	struct sockaddr_in from_addr,to_addr;
	socklen_t from_addr_sz;
	int str_len;
	char message[BUF_SIZE];
	if(argc!=3)
	{
		fprintf(stderr,"Usage : %s <IP> <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sock==-1)
		error_handling("socket() error!");
	memset(&to_addr,0,sizeof(to_addr));
	to_addr.sin_family=AF_INET;
	if(!inet_aton(argv[1],&to_addr.sin_addr))
		error_handling("IP error!");
	to_addr.sin_port=htons(atoi(argv[2]));
	from_addr_sz=sizeof(from_addr);
	connect(sock,(struct sockaddr *)&to_addr,sizeof(to_addr));
	fputs("Insert message(q to quit): ",stdout);
	fgets(message,BUF_SIZE,stdin);
	write(sock,message,strlen(message));

	while(count<10)
	{
		str_len=read(sock,message,BUF_SIZE);
		message[str_len]='\0';
		printf("count %d  Message from server: %s",++count,message);
		write(sock,message,strlen(message));
	}
	close(sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
