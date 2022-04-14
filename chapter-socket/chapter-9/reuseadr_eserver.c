#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define TRUE 1
#define FALSE 0
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int serv_sock,clnt_sock;
	int option,str_len;
	char message[30];
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t optlen,clnt_addr_sz;
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serv_sock==-1)
		error_handling("socket() error!");
	option=TRUE;
	optlen=sizeof(option);
	setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void *)&option,optlen);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error!");
	if(listen(serv_sock,1)==-1)
		error_handling("listen() error!");
	clnt_addr_sz=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
	while((str_len=read(clnt_sock,message,sizeof(message)))!=0)
	{
		write(clnt_sock,message,str_len);
		write(1,message,str_len);
	}
	close(clnt_sock);
	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
