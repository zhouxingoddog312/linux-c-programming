#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	int fd;
	FILE *fp;
	fd=open("data",O_WRONLY|O_CREAT|O_TRUNC,0664);
	if(fd==-1)
	{
		fputs("file open error\n",stderr);
		return -1;
	}
	fp=fdopen(fd,"w");
	fputs("Network c programing\n",fp);
	fclose(fp);
	return 0;
}
