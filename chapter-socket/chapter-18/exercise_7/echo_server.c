#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#define BUF_SIZE 1024
void error_handling(char *message);
void *handle_clnt(void *arg);
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
char message[BUF_SIZE];
int main(int argc,char *argv[])
{
	pthread_t t_id;
	int serv_sock,clnt_sock;
	int str_len,i;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_sz;
	if(argc!=2)
	{
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serv_sock==-1)
		error_handling("socket() error!");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error!");
	if(listen(serv_sock,5)==-1)
		error_handling("listen() error!");
	clnt_addr_sz=sizeof(clnt_addr);
	while(1)
	{
		clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
		if(clnt_sock==-1)
			error_handling("accept() error!");
		else
			printf("Connected client %d\n",i+1);
		pthread_create(&t_id,NULL,handle_clnt,(void *)&clnt_sock);
		pthread_detach(t_id);
	}
	close(serv_sock);
	exit(0);
}
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
void *handle_clnt(void *arg)
{
	int sock=*((int *)arg);
	int str_len;
	pthread_mutex_lock(&mutex);
	while((str_len=read(sock,message,BUF_SIZE))!=0)
		write(sock,message,str_len);
	pthread_mutex_unlock(&mutex);
	close(sock);
	pthread_exit(NULL);
}
