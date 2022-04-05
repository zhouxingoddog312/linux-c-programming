#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define PATH_LEN 100
/*客户端向服务器端传送文件名以$结尾
 * 客户端参数为IP地址、端口、文件路径（绝对路径）
 * 客户端接收到4字节整型代表文件大小，-1代表文件不存在*/
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int serv_sock,fd;
	char buf[BUF_SIZE];
	char file_name[PATH_LEN];
	struct sockaddr_in serv_addr;
	int result;
	int path_len;
	int buf_len;
	int totle_len;
	if(argc!=4)
	{
		fprintf(stderr,"Usage : %s <IP> <port> <path>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serv_sock==-1)
		error_handling("socket() error!");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error!");
	strcpy(file_name,argv[3]);
	path_len=strlen(file_name);
	file_name[path_len]='$';
	write(serv_sock,file_name,path_len+1);
	read(serv_sock,&result,sizeof(result));
	if(result==-1)
		fprintf(stderr,"no such file %s\n",argv[3]);
	else
	{
		fd=open(argv[3],O_WRONLY|O_TRUNC|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP);
		if(fd==-1)
			error_handling("open() error!");
		totle_len=0;
		while(result>totle_len)
		{
			buf_len=read(serv_sock,buf,BUF_SIZE);
			write(fd,buf,buf_len);
			totle_len+=buf_len;
		}
		close(fd);
	}
	close(serv_sock);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
