#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv)
{
	char *var,*value;
	if(argc==1||argc>3)
	{
		fprintf(stderr,"usage: environ var [value]\n");
		exit(EXIT_FAILURE);
	}
	var=argv[1];
	value=getenv(var);
	if(value)
		fprintf(stdout,"Variable %s has value %s\n",var,value);
	else
		printf("Variable %s has no value\n",var);
	if(argc==3)
	{
		char *string;
		value=argv[2];
		string=malloc(strlen(var)+strlen(value)+2);
		if(!string)
		{
			fprintf(stderr,"Out of memory\n");
			exit(EXIT_FAILURE);
		}
		strcpy(string,var);
		strcat(string,"=");
		strcat(string,value);
		printf("Calling putenv with: %s\n",string);
		if(putenv(string)!=0)
		{
			fprintf(stderr,"putenv failed\n");
			free(string);
			exit(EXIT_FAILURE);
		}
		value=getenv(var);
		if(value)
			printf("New value of %s is %s\n",var,value);
		else
			printf("New value of %s is NULL??\n",var);
	}
	exit(0);
}
