#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 100
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int so_brd=1;
	int send_sock;
	struct sockaddr_in mul_addr;
	FILE *fp;
	char buf[BUF_SIZE];
	if(argc!=3)
	{
		fprintf(stderr,"Usage : %s <Broadcast IP> <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	send_sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	memset(&mul_addr,0,sizeof(mul_addr));
	mul_addr.sin_family=AF_INET;
	mul_addr.sin_addr.s_addr=inet_addr(argv[1]);
	mul_addr.sin_port=htons(atoi(argv[2]));
	setsockopt(send_sock,SOL_SOCKET,SO_BROADCAST,(void *)&so_brd,sizeof(so_brd));
	if((fp=fopen("news.txt","r"))==NULL)
	{
		error_handling("fopen() error!");
	}
	while(!feof(fp))
	{
		fgets(buf,BUF_SIZE,fp);
		sendto(send_sock,buf,strlen(buf),0,(struct sockaddr *)&mul_addr,sizeof(mul_addr));
		sleep(2);
	}
	fclose(fp);
	close(send_sock);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
