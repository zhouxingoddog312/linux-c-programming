#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(void)
{
	time_t timeval;
	struct tm *tm_ptr;
	time(&timeval);
	tm_ptr=localtime(&timeval);
	printf("The date from asctime is %s\n",asctime(tm_ptr));
	printf("The date from ctime is %s\n",ctime(&timeval));
	exit(0);
}
