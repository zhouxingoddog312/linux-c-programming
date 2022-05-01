#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#define BUF_SIZE 100
#define EPOLL_SIZE 256
#define CLNT_MAX 255
void error_handling(char *message);
void setnonblockingmode(int fd);
int main(int argc,char *argv[])
{
	int index;
	int clnt_socks[CLNT_MAX];
	int clnt_cnt=0;
	int serv_sock,clnt_sock;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_sz;
	int str_len,i;
	char buf[BUF_SIZE];

	struct epoll_event event;
	struct epoll_event *ep_events;
	int epfd,event_cnt;
	if(argc!=2)
	{
		fprintf(stderr,"Usage : %s\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	clnt_addr_sz=sizeof(clnt_addr);
	serv_sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serv_sock==-1)
		error_handling("socket() error!");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() error!");
	if(listen(serv_sock,5)==-1)
		error_handling("listen() error!");
	setnonblockingmode(serv_sock);
	epfd=epoll_create(EPOLL_SIZE);
	ep_events=malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
	event.data.fd=serv_sock;
	event.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);
	while(1)
	{
		event_cnt=epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);
		if(event_cnt==-1)
		{
			puts("epoll_wait() error!");
			break;
		}
		for(i=0;i<event_cnt;i++)
		{
			if(ep_events[i].data.fd==serv_sock)
			{
				clnt_sock=accept(ep_events[i].data.fd,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
				setnonblockingmode(clnt_sock);
				clnt_socks[clnt_cnt++]=clnt_sock;
				event.data.fd=clnt_sock;
				event.events=EPOLLIN|EPOLLET;
				epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sock,&event);
				printf("connected client IP: %s\n",inet_ntoa(clnt_addr.sin_addr));
			}
			else
			{
				while(1)
				{
					str_len=read(ep_events[i].data.fd,buf,BUF_SIZE);
					if(str_len==0)
					{
						for(index=0;index<clnt_cnt;index++)
						{
							if(clnt_sock==clnt_socks[index])
							{
								while(index<clnt_cnt-1)
								{
									clnt_socks[index]=clnt_socks[index+1];
									index++;
								}
								break;
							}
						}
						clnt_cnt--;
						epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);
						close(ep_events[i].data.fd);
						printf("Close connected: %d\n",ep_events[i].data.fd);
						break;
					}
					else if(str_len<0)
					{
						if(errno==EAGAIN)
							break;
					}
					else
					{
						for(index=0;index<clnt_cnt;index++)
							write(clnt_socks[index],buf,str_len);
					}
				}
			}
		}
	}
	free(ep_events);
	close(epfd);
	close(serv_sock);
	exit(0);
}
void error_handling(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(EXIT_FAILURE);
}
void setnonblockingmode(int fd)
{
	int flag=fcntl(fd,F_GETFL,0);
	fcntl(fd,F_SETFL,flag|O_NONBLOCK);
}
