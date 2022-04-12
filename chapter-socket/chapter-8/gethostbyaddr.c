#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int i;
	struct sockaddr_in addr;
	struct hostent *host;
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <IP>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	memset(&addr,0,sizeof(addr));
	addr.sin_addr.s_addr=inet_addr(argv[1]);
	host=gethostbyaddr((char *)&addr.sin_addr,4,AF_INET);
	if(!host)
		error_handling("gethostbyaddr() error!");
	printf("Official name: %s\n",host->h_name);
	for(i=0;host->h_aliases[i];i++)
		printf("Aliases %d: %s\n",i+1,host->h_aliases[i]);
	printf("Address type is %s, len = %d\n",(host->h_addrtype==AF_INET)?"AF_INET":"AF_INET",host->h_length);
	for(i=0;host->h_addr_list[i];i++)
		printf("Address %d : %s\n",i+1,inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
