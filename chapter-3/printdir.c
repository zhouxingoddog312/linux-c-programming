#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
void printdir(char *dir,int depth);
int main(int argc,char *argv[])
{
	char *topdir=".";
	if(argc>=2)
		topdir=argv[1];
	fprintf(stdout,"Directory scan of %s:\n",topdir);
	printdir(topdir,0);
	fprintf(stdout,"Done!\n");
	exit(0);
}
void printdir(char *dir,int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp=opendir(dir))==NULL)
	{
		fprintf(stderr,"can not open directory: %s\n",dir);
		return;
	}
	chdir(dir);
	while((entry=readdir(dp))!=NULL)
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
				continue;
			fprintf(stdout,"%*s%s/\n",depth," ",entry->d_name);
			printdir(entry->d_name,depth+4);
		}
		else
			fprintf(stdout,"%*s%s\n",depth," ",entry->d_name);
	}
	chdir("..");
	closedir(dp);
}
