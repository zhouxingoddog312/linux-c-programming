#include <stdio.h>
#include <stdlib.h>
#define size 1024
int main(void)
{
	FILE *in,*out;
	char block[size];
	in=fopen("file.in","r");
	out=fopen("file.out","w");
	while(fgets(block,size,in)!=NULL)
		fputs(block,out);
	exit(0);
}
