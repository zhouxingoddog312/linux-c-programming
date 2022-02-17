#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
	const char some_data[]="123";
	int data_processed;
	int file_pipes[2];
	pid_t fork_result;
	char buffer[BUFSIZ+1];
	memset(buffer,'\0',sizeof(buffer));
	if(pipe(file_pipes)==0)
	{
		fork_result=fork();
		if(fork_result==-1)
		{
			fprintf(stderr,"fork failure");
			exit(EXIT_FAILURE);
		}
		if(fork_result==0)
		{
			sprintf(buffer,"%d",file_pipes[0]);
			execl("pipe4","pipe4",buffer,(char *)0);
			exit(EXIT_FAILURE);
		}
		else
		{
			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			printf("%d - wrote %d bytes\n",getpid(),data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}
