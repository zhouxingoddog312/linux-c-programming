#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
	int data_processed;
	int file_pipes[2];
	pid_t fork_result;
	const char some_data[]="123";
	char buffer[BUFSIZ+1];
	memset(buffer,'\0',sizeof(buffer));
	if(pipe(file_pipes)==0)
	{
		fork_result=fork();
		if(fork_result==-1)
		{
			fprintf(stderr,"Fork failure");
			exit(EXIT_FAILURE);
		}
		if(fork_result==0)
		{
			data_processed=read(file_pipes[0],buffer,BUFSIZ);
			printf("pid: %d Read %d bytes: %s\n",getpid(),data_processed,buffer);
			exit(EXIT_SUCCESS);
		}
		else
		{
			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			printf("pid: %d Write %d bytes\n",getpid(),data_processed);
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_FAILURE);
}
