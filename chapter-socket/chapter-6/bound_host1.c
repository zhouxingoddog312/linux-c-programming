#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 50
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	struct sockaddr_in my_addr,your_addr;
	socklen_t your_addr_sz;
	int str_len,i;
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sock==-1)
		error_handling("socket() error!");
	memset(&my_addr,0,sizeof(my_addr));
	my_addr.sin_family=AF_INET;
	my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	my_addr.sin_port=htons(atoi(argv[1]));
	if(bind(sock,(struct sockaddr *)&my_addr,sizeof(my_addr))==-1)
		error_handling("bind() error!");
	your_addr_sz=sizeof(your_addr);
	for(i=0;i<3;i++)
	{
		sleep(5);
		str_len=recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr *)&your_addr,&your_addr_sz);
		printf("Message %d: %s\n",i+1,message);
	}
	close(sock);
	exit(0);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
