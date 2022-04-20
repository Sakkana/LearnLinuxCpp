#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    // 1.创建管道
    int ret = access("pipeAtoB", F_OK);
    if(ret == -1)
    {
        printf("pipeAtoB not exist, making...\n");
        ret = mkfifo("pipeAtoB", 0664);
        if(ret == -1)
        {
            perror("mkpipe");
            exit(0);
        }
    }

    ret = access("pipeBtoA", F_OK);
    if(ret == -1)
    {
        printf("pipeBtoA not exist, making...\n");
        ret = mkfifo("pipeBtoA", 0664);
        if(ret == -1)
        {
            perror("mkpipe");
            exit(0);
        }
    }

    // 2.以 write-only 的权限打开管道pipeAtoB
    int fdw = open("pipeAtoB", O_WRONLY);
    if(fdw == -1)
    {
        perror("open");
        exit(0);
    }
    printf("pipeAtoB is opened, right: write-only,pid = %d\n", getpid());

    // 3.以 read-only 的权限打开管道pipeBtoA
    int fdr = open("pipeBtoA", O_RDONLY);
    if(fdw == -1)
    {
        perror("open");
        exit(0);
    }
    printf("pipeBtoA is opened, right: read-only, pid = %d\n", getpid());

    // 4.开始通信
    char buf[128];

    int pid = fork();
    if(pid > 0)
    {
        while (1)
        {
            // 写数据
            memset(buf, 0, sizeof buf);
            fgets(buf, sizeof(buf), stdin);
            ret = write(fdw, buf, strlen(buf));
            if(ret == -1)
            {
                perror("write");
                exit(0);
            }
        }
    }else if(pid == 0)
    {
        while (1)
        {
            // 读数据
            memset(buf, 0, sizeof buf);
            ret = read(fdr, buf, sizeof(buf));
            if(ret <= 0)    // 读取失败/对面关闭管道/数据读完/读取失败
            {
                perror("read");
                exit(0);
            }else
                printf("对方来信：%s", buf);
        }
    }else
    {
        perror("fork");
        exit(0);
    }

    // 5. 关闭文件描述符
    close(fdw);
    close(fdr);

    return 0;
}