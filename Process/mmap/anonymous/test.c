
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{

    // 1. 创建匿名内存映射区
    int length = 4096;
    void *ptr = mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);     // fd:-1, offset:0
    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    // 2. 父子间间通信
    pid_t pid = fork();
    if(pid > 0)
    {
        strcpy((char *)ptr, "hello, son!");
        wait(NULL);
    }else if(pid == 0)
    {
        sleep(1);   // 内存映射是非阻塞的，因此子进程要在父进程结束后执行
        printf("son received: %s\n", (char *)ptr);
    }

    int ret = munmap(ptr, length);
    if(ret == -1)
    {
        perror("munmap");
        return -1;
    }

    return 0;
}