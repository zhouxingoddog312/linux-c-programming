#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
	struct tm *tm_ptr;
	time_t the_time;
	time(&the_time);
	tm_ptr=localtime(&the_time);
	printf("Raw time is %ld\n",the_time);
	printf("localmtime gives:\n");
	printf("date: %04d/%02d/%02d\n",tm_ptr->tm_year+1900,tm_ptr->tm_mon+1,tm_ptr->tm_mday);
	printf("time: %02d:%02d:%02d\n",tm_ptr->tm_hour,tm_ptr->tm_min,tm_ptr->tm_sec);
	exit(0);
}
