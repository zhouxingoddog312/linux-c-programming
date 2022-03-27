#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
void error_handling(char *message);
int main(void)
{
	int fd;
	char buf[]="let's go!";
	fd=open("data.txt",O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
	if(fd==-1)
		error_handling("open() error!");
	printf("file descripter %d\n",fd);
	if(write(fd,buf,sizeof(buf))==-1)
		error_handling("write() error!");
	close(fd);
	exit(0);
}
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
