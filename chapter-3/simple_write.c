#include <unistd.h>
#include <stdlib.h>
int main(void)
{
	if(write(1,"Here is some data\n",18)!=18)
		write(2,"A write error has occurred on file descriptor 1\n",49);
	exit(0);
}
