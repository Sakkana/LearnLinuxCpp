#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // 需要在 fork 之前创建管道，这样两个进程才会共享文件描述符
    int pipefd[2];  // 传出参数
    int ret = pipe(pipefd);
    if(ret == -1)
    {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();

    if(pid > 0)
    {
        printf("I'm parent pid=%d. I'm going to read sth to my papa through a pipe.\n", getpid());
        
        // 父进程关闭写端
        close(pipefd[1]);

        char buf[1024] = {0};
        while(1)
        {
            // 父进程专心读数据
            int len = read(pipefd[0], buf, sizeof(buf));  
            printf("parent receive: %sn", buf);
        }

    }else if(pid == 0)
    {
        printf("I'm child pid=%d. I'm going to send sth to my papa through a pipe.\n", getpid());
 
        // 子进程关闭读端
        close(pipefd[0]);

        char buf[1024] = {0};
        while(1)
        {
            // 子进程专心写数据
            char *str = "Hello, I'm child\n";
            write(pipefd[1], str, strlen(str)); // 儿子把数据写道pipefd[1]
        }
    }

    return 0;
}