#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE *in,*out;
	char *line=NULL;
	size_t n=0;
	int nread;
	in=fopen("file.in","r");
	out=fopen("file.out","w");
	while((nread=getline(&line,&n,in))>0)
		printf("nread=%d\n",nread);
		//fwrite(line,sizeof(char),nread,out);
	free(line);
	exit(0);
}
