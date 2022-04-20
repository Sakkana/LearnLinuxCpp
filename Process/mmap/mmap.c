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
    // 1. 打开一个磁盘文件
    int fd = open("share.txt", O_RDWR | O_CREAT);

    // 2. 获取文件大小
    int size = lseek(fd, 0, SEEK_END);  // fd, offset, where

    // 3. 创建内存映射区
    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    close(fd);
    

    // 4. 创建子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        wait(NULL);

        // 读取内存
        char buf[64];
        strcpy(buf, (char *)ptr);
        printf("%s\n", buf);
        
    }else if(pid == 0)
    {
        // 操作内存
        strcpy((char *)ptr, "hello, papa!!!");
    }else
    {
        perror("fork");
        exit(0);
    }

    // 5. 关闭内存映射区
    munmap(ptr, size);
    

    return 0;
}