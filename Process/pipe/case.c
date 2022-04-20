#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

    实现 ps aux | grpe

    子进程： ps aux，子进程结束后，将数据发送给父进程
    父进程：获取数据，打印

    pipe(), execlp()
    但是子进程默认把数据默认把数据发送到子进程对应的终端，即 std_fileno
    因此需要dup2复制文件描述符，将数据重定向到管道的写端

*/

int main()
{
    // 创建一个匿名管道
    int fd[2];
    int ret = pipe(fd);

    if(ret == -1)
    {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        // 关闭写端
        close(fd[1]);

        // 从管道中读取数据
        char buf[1024] = {0};

        int len = -1;
        while(len = (read(fd[0], buf, sizeof(buf) - 1)) > 0)
        {
            printf("%s", buf);
            memset(buf, 0, sizeof buf);
        }

        // 回收子进程资源
        wait(NULL);

    }else if(pid == 0)
    {
        // 关闭读端
        close(fd[0]);

        // 文件描述符重定向 stdout_fileno -> fd[1]，使得ps aux写入管道的写端
        int file = open("psaux.txt", O_CREAT | O_RDWR, 0664);

        dup2(file, STDOUT_FILENO);
        
        // 执行 ps aux
        char *str = "if you saw this it might succeed.\n";
        write(fd[1], str, strlen(str));
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(0);

    }else
    {
        perror("fork");
        exit(0);
    }

    

    return 0;
}