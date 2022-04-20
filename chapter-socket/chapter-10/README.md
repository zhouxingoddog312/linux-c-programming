1. c d
2. a c d
3. 
```c
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main(void)
{
        int sock;
        sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
        pid_t pid=fork();
        if(pid==0)
                printf("sock : %d\n",sock);
        else
                printf("sock : %d\n",sock);
        close(sock);
        return 0;
}
```
4. 因为子进程在把返回的值传递给父进程之前，或者父进程销毁之前，这段时间内子进程将变为僵尸进程。预防子进程成为僵尸进程，可以让父进程主动获取子进程的返回值，利用wait或waitpid等函数。
5.   
```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
int flag=0;
void ctrlc(int sig)
{
        char ch;
        if(sig==SIGINT)
        {
                fputs("是否确定退出程序：",stdout);
                ch=getchar();
                if(ch=='y'||ch=='Y')
                        flag=1;
                else
                        ;
        }
}
int main(void)
{
        struct sigaction act;
        act.sa_flags=0;
        sigemptyset(&act.sa_mask);
        act.sa_handler=ctrlc;
        sigaction(SIGINT,&act,0);
        while(!flag)
        {
                puts("continue...");
                sleep(2);
        }
        return 0;
}
```
```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
void ctrlc(int sig)
{
        if(sig==SIGALRM)
        {
                fputs("1秒后继续输出\n",stdout);
                alarm(1);
        }
}
int main(void)
{
        struct sigaction act;
        act.sa_flags=0;
        sigemptyset(&act.sa_mask);
        act.sa_handler=ctrlc;
        sigaction(SIGALRM,&act,0);
        alarm(1);
        while(1)
                sleep(10);
        return 0;
}
```