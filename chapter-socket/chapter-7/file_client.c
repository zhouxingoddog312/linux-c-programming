#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 50
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char buf[BUF_SIZE];
	FILE *fp;
	int read_cnt;
	if(argc!=3)
	{
		fprintf(stderr,"Usage : %s <IP> <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock==-1)
		error_handling("socket() error!");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	fp=fopen("file_server.dat","wb");
	while((read_cnt=read(sock,buf,BUF_SIZE))>0)
		fwrite(buf,1,read_cnt,fp);
	puts("Recieved file data!");
	write(sock,"Thank you.",11);
	close(sock);
	fclose(fp);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
