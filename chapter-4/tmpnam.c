#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char template1[]="templatefileXXXXXX";
	char template2[]="123XXXXXX";
	char tmpname[L_tmpnam];
	char *filename;
	FILE *tmpfp;
	int fd;
	filename=tmpnam(tmpname);
	printf("Temporary file name is: filename=%s	tmpname=%s\n",filename,tmpname);
	tmpfp=tmpfile();
	if(tmpfp)
		printf("Open a temporary file OK.\n");
	else
		perror("tmpfile");
	fclose(tmpfp);
	filename=mktemp(template1);
	printf("Temporary file name from mktemp is: %s\n",filename);
	fd=mkstemp(template2);
	if(fd!=-1)
		printf("Open a temporary file with mkstemp OK.\n");
	else
		perror("mkstemp");
	unlink(template2);
	exit(0);
}
