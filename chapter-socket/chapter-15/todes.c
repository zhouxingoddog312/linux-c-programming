#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	FILE *fp;
	int fd;
	fd=open("data",O_WRONLY|O_CREAT|O_TRUNC,0664);
	if(fd==-1)
	{
		fputs("file open error.\n",stderr);
		return -1;
	}
	printf("First file descriptor: %d\n",fd);
	fp=fdopen(fd,"w");
	fputs("TCP/IP SOCKET PROGRAMING\n",fp);
	printf("Seconde file descriptor: %d\n",fileno(fp));
	fclose(fp);
	return 0;
}
