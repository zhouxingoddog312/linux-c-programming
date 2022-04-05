#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 1024
#define PATH_LEN 100
/*客户端传来文件名以$标识结尾
 * 服务器向客户端传输4字节整型代表文件大小，-1代表文件不存在
 * 服务器向客户端传输文件*/
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int serv_sock,clnt_sock,fd;
	char buf[BUF_SIZE];
	char file_name[PATH_LEN];
	char ch;
	int index;
	int result;
	int buf_len;
	struct stat file_info;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_len;
	clnt_addr_len=sizeof(clnt_addr);
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
	while(true)
	{
		clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_len);
		if(clnt_sock==-1)
			error_handling("accept() error!");
		else
			printf("Connected client......\n");
		index=0;
		while(read(clnt_sock,&ch,1)>0)
		{
			if(ch!='$')
			{
				file_name[index++]=ch;
			}
			else
				break;
		}
		file_name[index]='\0';
		if(!access(file_name,F_OK|R_OK))
		{//文件存在且可读
			stat(file_name,&file_info);
			result=file_info.st_size;
			write(clnt_sock,&result,sizeof(result));
			fd=open(file_name,O_RDONLY);
			if(fd==-1)
				error_handling("open() error!");
			while((buf_len=read(fd,buf,BUF_SIZE))>0)
				write(clnt_sock,buf,buf_len);
			close(fd);
		}
		else//文件不存在
		{
			result=-1;
			write(clnt_sock,&result,sizeof(result));
		}
		close(clnt_sock);
		printf("Connect off!\n");
	}
	close(serv_sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
