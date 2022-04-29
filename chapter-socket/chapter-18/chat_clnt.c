#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#define BUF_SIZE 100
#define NAME_SIZE 20
void *send_msg(void *arg);
void *recv_msg(void *arg);
void error_handling(char *msg);
char msg[BUF_SIZE];
char name[NAME_SIZE]="[default]";
int main(int argc,char *argv[])
{
	pthread_t t_id1,t_id2;
	void *pthread_result;
	int sock;
	struct sockaddr_in sock_addr;
	if(argc!=4)
	{
		fprintf(stderr,"Usage : %s <IP> <port> <name>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	sprintf(name,"%s",argv[3]);
	sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	memset(&sock_addr,0,sizeof(sock_addr));
	sock_addr.sin_family=AF_INET;
	inet_aton(argv[1],&sock_addr.sin_addr);
	sock_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock,(struct sockaddr *)&sock_addr,sizeof(sock_addr))==-1)
		error_handling("connect() error!");
	pthread_create(&t_id1,NULL,send_msg,(void *)&sock);
	pthread_create(&t_id2,NULL,recv_msg,(void *)&sock);
	pthread_join(t_id1,NULL);
	pthread_join(t_id2,&pthread_result);
	close(sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *msg)
{
	fprintf(stderr,"%s\n",msg);
	exit(EXIT_FAILURE);
}
void *send_msg(void *arg)
{
	int sock=*((int *)arg);
	char name_msg[BUF_SIZE+NAME_SIZE];
	while(1)
	{
		fgets(msg,BUF_SIZE,stdin);
		if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n"))
		{
			close(sock);
			exit(0);
		}
		sprintf(name_msg,"%s %s",name,msg);
		write(sock,name_msg,strlen(name_msg));
	}
	pthread_exit(NULL);
}
void *recv_msg(void *arg)
{
	int str_len;
	int sock=*((int *)arg);
	char name_msg[BUF_SIZE+NAME_SIZE];
	while(1)
	{
		str_len=read(sock,name_msg,BUF_SIZE+NAME_SIZE-1);
		if(str_len==-1)
			pthread_exit((void *)-1);
		name_msg[str_len]='\0';
		fputs(name_msg,stdout);
	}
	pthread_exit(NULL);
}
