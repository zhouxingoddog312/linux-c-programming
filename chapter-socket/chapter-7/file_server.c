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
	int serv_sock,clnt_sock;
	char buf[BUF_SIZE];
	int read_cnt;
	FILE *fp;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_sz;
	if(argc!=2)
	{
		fprintf(stderr,"Usage %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serv_sock==-1)
		error_handling("sock() error!");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error!");
	listen(serv_sock,5);
	clnt_addr_sz=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
	fp=fopen("file_server.c","rb");
	while(1)
	{
		read_cnt=fread(buf,1,BUF_SIZE,fp);
		if(read_cnt<BUF_SIZE)
		{
			write(clnt_sock,buf,read_cnt);
			break;
		}
		write(clnt_sock,buf,BUF_SIZE);
	}
	fclose(fp);
	shutdown(clnt_sock,SHUT_WR);
	read(clnt_sock,buf,BUF_SIZE);
	printf("Message from client : %s\n",buf);
	close(clnt_sock);
	close(serv_sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
