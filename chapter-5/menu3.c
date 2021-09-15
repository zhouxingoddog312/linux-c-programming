#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
char *menu[]=
{
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL
};
int getchoice(char *greet,char *choices[],FILE *in,FILE * out);
int main(void)
{
	FILE *input,*output;
	int choice=0;
	if(!isatty(fileno(stdout)))
	{
		fprintf(stderr,"You are not a terminal!\n");
	}
	input=fopen("/dev/tty","r");
	output=fopen("/dev/tty","w");
	if(!input||!output)
	{
		fprintf(stderr,"Unable to open /dev/tty\n");
		exit(1);
	}
	do
	{
		choice=getchoice("Please select an action",menu,input,output);
		printf("You have chosen: %c\n",choice);
	}
	while(choice!='q');
	exit(0);
}
int getchoice(char *greet,char *choices[],FILE *in,FILE * out)
{
	int chosen=0;
	int selected;
	char **option;
	do
	{
		option=choices;
		fprintf(out,"Choice: %s\n",greet);
		while(*option)
		{
			fprintf(out,"%s\n",*option);
			option++;
		}
		do
		{
			selected=getc(in);
		}
		while(selected=='\n');
		option=choices;
		while(*option)
		{
			if(selected==*option[0])
			{
				chosen=1;
				break;
			}
			option++;
		}
		if(!chosen)
			fprintf(out,"Incorrect choice, select again\n");
	}
	while(!chosen);
	return selected;
}
