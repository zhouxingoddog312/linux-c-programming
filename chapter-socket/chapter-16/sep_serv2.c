#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 1024
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int serv_sock,clnt_sock,clnt_sock_write;
	struct sockaddr_in serv_addr,clnt_addr;
	int str_len,i;
	FILE *writefp,*readfp;
	socklen_t clnt_addr_sz;
	char buf[BUF_SIZE];
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error!");
	if(listen(serv_sock,5)==-1)
		error_handling("listen() error!");
	clnt_addr_sz=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
	clnt_sock_write=dup(clnt_sock);
	readfp=fdopen(clnt_sock,"r");
	writefp=fdopen(clnt_sock_write,"w");
	fputs("From server: hi client!",writefp);
	fputs("I love all of the world!",writefp);
	fflush(writefp);
	shutdown(clnt_sock_write,SHUT_WR);
	fclose(writefp);
	fgets(buf,BUF_SIZE,readfp);
	fputs(buf,stdout);
	fclose(readfp);
	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
