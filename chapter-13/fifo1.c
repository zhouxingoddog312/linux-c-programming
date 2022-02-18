#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
int main(void)
{
	int res=mkfifo("/tmp/my_fifo",0666);
	if(res==0)
		printf("FIFO created\n");
	else if(res==-1)
		if(errno==EEXIST)
			perror("/tmp/my_fifo");
	exit(EXIT_SUCCESS);
}
