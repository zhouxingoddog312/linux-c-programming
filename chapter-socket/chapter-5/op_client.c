#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
void error_handling(char *message);
int main(int argc,char *argv[])
{
	char ch;
	int sock;
	char opmsg[BUF_SIZE];
	int result,op_cnt,i;
	struct sockaddr_in serv_addr;
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
	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error!");
	else
		puts("Connected......");
	fputs("Operand count: ",stdout);
	scanf("%d",&op_cnt);
	opmsg[0]=(char)op_cnt;
	for(i=0;i<op_cnt;i++)
	{
		printf("Operand %d: ",i+1);
		scanf("%d",&opmsg[i*OPSZ+1]);
	}
	while((ch=getchar())!='\n')
		;
	fputs("Operator: ",stdout);
	scanf("%c",&opmsg[op_cnt*OPSZ+1]);
	write(sock,opmsg,op_cnt*OPSZ+2);
	read(sock,&result,RLT_SIZE);
	printf("Operation result: %d\n",result);
	close(sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
