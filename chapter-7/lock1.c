#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
int main(void)
{
	int file_desc;
	int save_errno;
	file_desc=open("/tmp/LCK.test",O_RDWR|O_CREAT|O_EXCL,0444);
	if(file_desc==-1)
	{
		save_errno=errno;
		printf("Open failed with error %d\n",save_errno);
	}
	else
		printf("Open successed\n");
	exit(EXIT_SUCCESS);
}
