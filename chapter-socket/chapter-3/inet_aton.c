#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
void error_handling(char *message);
int main(void)
{
	char *addr="127.232.124.79";
	struct sockaddr_in addr_inet;
	if(!inet_aton(addr,&addr_inet.sin_addr))
		error_handling("inet_aton() error!");
	else
		printf("Network ordered integer addr : %#x\n",addr_inet.sin_addr.s_addr);
	exit(EXIT_SUCCESS);
}
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
