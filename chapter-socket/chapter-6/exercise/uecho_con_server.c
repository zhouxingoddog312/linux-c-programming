#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 50
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int count=0;
	int sock;
	char message[BUF_SIZE];
	int str_len;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_sz;
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sock==-1)
		error_handling("socket() error!");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error!");
	clnt_addr_sz=sizeof(clnt_addr);
		
	
	str_len=recvfrom(sock,(void *)message,BUF_SIZE,0,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
	connect(sock,(struct sockaddr *)&clnt_addr,clnt_addr_sz);
	while(count<10)
	{
		message[str_len]='\0';
		printf("count %d  Message from client: %s",++count,message);
		write(sock,message,strlen(message));
		read(sock,message,BUF_SIZE);
	}
	

	close(sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
