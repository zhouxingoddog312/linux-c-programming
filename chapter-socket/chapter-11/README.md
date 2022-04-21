1. 两个不同的进存通过操作系统提供的可以同时访问的内存空间交换数据.
2. 由于两个不同进程之间不共享内存，所以需要有操作系统提供共享的内存空间。
3. 由pipe函数创建路径，实际由操作系统创建管道。在调用fork()函数时会自动复制管道的文件描述符。双向通信中需要注意最好不要用一条管道进行读写操作。
4. 
```c
#include <unistd.h>
#include <stdio.h>
#define BUF_SIZE 50
int main(void)
{
        int fds1[2],fds2[2];
        pid_t pid;
        pipe(fds1);
        pipe(fds2);
        pid=fork();
        if(pid==0)
        {
                int result;
                close(fds1[0]);
                close(fds2[1]);
                int i=0,index;
                for(index=0;index<3;i++,index++)
                {
                        write(fds1[1],&i,sizeof(i));
                        read(fds2[0],&result,sizeof(result));
                        printf("Child proc : %d\n",result);
                }
        }
        else
        {
                int result;
                close(fds1[1]);
                close(fds2[0]);
                int i=0,index;
                for(index=0;index<3;i++,index++)
                {
                        write(fds2[1],&i,sizeof(i));
                        read(fds1[0],&result,sizeof(result));
                        printf("Parent proc : %d\n",result);
                }
        }
        return 0;
}
```