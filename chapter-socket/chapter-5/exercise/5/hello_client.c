#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int charcnt;
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len,strcnt;
	char str[]="Wo shi shei?";
	if(argc!=3)
	{
		printf("Usage : %s <IP> <port>\n",argv[0]);
		exit(1);
	}
	sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock==-1)
		error_handling("socket() error");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error");
	charcnt=strlen(str);
	write(sock,&charcnt,sizeof(charcnt));
	write(sock,str,strlen(str));
	read(sock,&charcnt,4);

	str_len=0;
	while(charcnt>str_len)
	{
		strcnt=read(sock,&message[str_len],29);
		str_len+=strcnt;
	}
	printf("read %s\n",message);
	close(sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
