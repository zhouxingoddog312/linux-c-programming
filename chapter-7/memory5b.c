#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	char z=*(const char *)0;
	printf("I read from location zero.\n");
	exit(EXIT_SUCCESS);
}
