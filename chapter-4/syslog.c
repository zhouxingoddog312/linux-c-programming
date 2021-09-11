#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE *fp;
	fp=fopen("not_here","r");
	if(!fp)
		syslog(LOG_ERR|LOG_USER,"oops - %m\n");
	exit(0);
}
