#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
	FILE *read_fp;
	char buffer[BUFSIZ+1];
	int chars_read;
	memset(buffer,'\0',sizeof(buffer));
	read_fp=popen("ps ax","r");
	if(read_fp!=NULL)
	{
		while((chars_read=fread(buffer,sizeof(char),BUFSIZ,read_fp))>0)
		{
			buffer[chars_read-1]='\0';
			printf("Reading %d:-\n%s\n",BUFSIZ,buffer);
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
