#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 50
void error_handling(char *message);
void read_childproc(int sig);
int main(int argc,char *argv[])
{
	int serv_sock,clnt_sock;
	struct sockaddr_in serv_addr,clnt_addr;
	struct sigaction act;
	socklen_t clnt_addr_sz;
	pid_t pid;
	int str_len,state;
	char buf[BUF_SIZE];
	int fds[2];
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <port>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	act.sa_handler=read_childproc;
	act.sa_flags=0;
	sigemptyset(&act.sa_mask);
	state=sigaction(SIGCHLD,&act,0);
	if(state==-1)
		error_handling("sigaction() error!");
	pipe(fds);
	pid=fork();
	if(pid==0)
	{
		close(fds[1]);
		FILE *fp=fopen("echomsg.txt","w");
		char msgbuf[BUF_SIZE];
		int i,len;
		for(i=0;i<10;i++)
		{
			len=read(fds[0],msgbuf,BUF_SIZE);
			fwrite(msgbuf,1,len,fp);
			fflush(fp);
		}
		fclose(fp);
		return 0;
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
			continue;
		else
			puts("new client connected...");
		pid=fork();
		if(pid==-1)
		{
			close(clnt_sock);
			continue;
		}
		if(pid==0)
		{
			close(serv_sock);
			while((str_len=read(clnt_sock,buf,BUF_SIZE))!=0)
			{
				write(clnt_sock,buf,str_len);
				write(fds[1],buf,str_len);
			}
			close(clnt_sock);
			puts("client disconnected...");
			return 0;
		}
		else
			close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
void read_childproc(int sig)
{
	int status;
	pid_t pid=waitpid(-1,&status,WNOHANG);
	printf("removed proc %d\n",pid);
}
