#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>
#define BUF_SIZE 1024
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int timecount=0;
	int serv_sock,clnt_sock;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_sz;
	int str_len,result;
	char buf[BUF_SIZE];
	fd_set reads,cpy_reads;
	int fd_max,i;
	struct timeval timeout;
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
	fd_max=serv_sock;
	FD_ZERO(&reads);
	FD_SET(serv_sock,&reads);
	while(timecount<10)
	{
		cpy_reads=reads;
		timeout.tv_sec=5;
		timeout.tv_usec=500;
		result=select(fd_max+1,&cpy_reads,0,0,&timeout);
		if(result==-1)
		{
			break;
		}
		else if(result==0)
		{
			fprintf(stdout,"timeout %d\n",++timecount);
			continue;
		}
		else
		{
			timecount=0;
			for(i=0;i<fd_max+1;i++)
			{
				if(FD_ISSET(i,&cpy_reads))
				{
					if(i==serv_sock)
					{
						clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
						FD_SET(clnt_sock,&reads);
						fd_max=clnt_sock>serv_sock?clnt_sock:serv_sock;
						printf("connect client: %d\n",clnt_sock);
					}
					else
					{
						str_len=read(i,buf,BUF_SIZE);
						if(str_len==0)
						{
							FD_CLR(i,&reads);
							close(i);
							printf("closed client: %d\n",i);
						}
						else
							write(i,buf,str_len);
					}
				}
			}
		}
	}
	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
