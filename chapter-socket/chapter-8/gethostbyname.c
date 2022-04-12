#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
void error_handling(char *message);
int main(int argc,char *argv[])
{
	int i;
	struct hostent *host;
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s <addr>",argv[0]);
		exit(EXIT_FAILURE);
	}
	host=gethostbyname(argv[1]);
	if(!host)
		error_handling("gethostbyname() error!");
	printf("Official name %s\n",host->h_name);
	for(i=0;host->h_aliases[i];i++)
		printf("Aliases %d: %s\n",i+1,host->h_aliases[i]);
	printf("Address type is %s,len=%d\n",(host->h_addrtype==AF_INET)?"AF_INET":"AF_INET6",host->h_length);
	for(i=0;host->h_addr_list[i];i++)
		printf("IP addr %d : %s\n",i+1,inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
	return 0;
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
