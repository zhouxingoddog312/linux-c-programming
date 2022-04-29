#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#define BUF_SIZE 100
#define CLNT_MAX 256
void *handle_clnt(void *arg);
void send_msg(char *msg,int len);
void error_handling(char *message);
int clnt_socks[CLNT_MAX];
int clnt_cnt=0;
pthread_mutex_t mutex;
int main(int argc,char *argv[])
{
	int serv_sock,clnt_sock;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_sz;
	clnt_addr_sz=sizeof(clnt_addr);
	pthread_t t_id;
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	pthread_mutex_init(&mutex,NULL);
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
	while(1)
	{
		clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
		pthread_mutex_lock(&mutex);
		clnt_socks[clnt_cnt++]=clnt_sock;
		pthread_mutex_unlock(&mutex);
		pthread_create(&t_id,NULL,handle_clnt,(void *)&clnt_sock);
		pthread_detach(t_id);
		printf("Connected client IP: %s\n",inet_ntoa(clnt_addr.sin_addr));
	}
	close(serv_sock);
	exit(EXIT_SUCCESS);
}
void *handle_clnt(void *arg)
{
	int clnt_sock,str_len,i;
	clnt_sock=*((int *)arg);
	char buf[BUF_SIZE];
	while((str_len=read(clnt_sock,buf,BUF_SIZE))!=0)
		send_msg(buf,str_len);
	pthread_mutex_lock(&mutex);
	for(i=0;i<clnt_cnt;i++)
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i<clnt_cnt-1)
			{
				clnt_socks[i]=clnt_socks[i+1];
				i++;
			}
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutex);
	close(clnt_sock);
	pthread_exit(NULL);
}
void send_msg(char *msg,int len)
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i=0;i<clnt_cnt;i++)
		write(clnt_socks[i],msg,len);
	pthread_mutex_unlock(&mutex);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
