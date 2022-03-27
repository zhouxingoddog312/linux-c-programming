#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
int main(void)
{
	int fd1,fd2,fd3;
	fd1=socket(PF_INET,SOCK_STREAM,0);
	fd2=open("test.dat",O_CREAT|O_WRONLY,S_IWUSR|S_IRUSR|S_IRGRP);
	fd3=socket(PF_INET,SOCK_DGRAM,0);
	printf("file descripter 1 : %d\n",fd1);
	printf("file descripter 2 : %d\n",fd2);
	printf("file descripter 3 : %d\n",fd3);
	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}
