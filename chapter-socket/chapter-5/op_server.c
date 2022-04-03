#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int calculate(int opnum,int opnds[],char oprator);
int main(int argc,char *argv[])
{
	int serv_sock,clnt_sock;
	char opinfo[BUF_SIZE];
	int result,op_cnt,i;
	int recv_cnt,recv_len;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_sz;
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
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
	for(i=0;i<5;i++)
	{
		op_cnt=0;
		clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
		read(clnt_sock,&op_cnt,1);
		recv_len=0;
		while(op_cnt*OPSZ+1>recv_len)
		{
			recv_cnt=read(clnt_sock,&opinfo[recv_len],BUF_SIZE-1);
			if(recv_cnt==-1)
				error_handling("read() error!");
			recv_len+=recv_cnt;
		}
		result=calculate(op_cnt,(int *)opinfo,opinfo[recv_len-1]);
		write(clnt_sock,(int *)&result,sizeof(result));
		close(clnt_sock);
	}
	close(serv_sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
int calculate(int opnum,int opnds[],char oprator)
{
	int result=opnds[0],i;
	switch(oprator)
	{
		case '+':
			for(i=1;i<opnum;i++)
				result+=opnds[i];
			break;
		case '-':
			for(i=1;i<opnum;i++)
				result-=opnds[i];
			break;
		case '*':
			for(i=1;i<opnum;i++)
				result*=opnds[i];
			break;
	}
	return result;
}
