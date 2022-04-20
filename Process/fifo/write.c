#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    // 1. 先判断管道文件是否存在，若不存在，创建
    int ret = access("myfifo", F_OK);
    if(ret == -1)
    {
        printf("管道不存在，正在为您创建...\n");

        // 2. 创建管道
        int ret = mkfifo("myfifo", 0664);
        if(ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }

    // 3.打开管道, 以 write-only 的权限打开
    int fd = open("myfifo", O_WRONLY);
    if(fd == -1)
    {
        perror("open");
        exit(0);
    }

    // 4.写数据
    for(int i = 0; i < 100; ++ i)
    {
        char buf[1024];
        sprintf(buf, "hello, %d\n", i);
        printf("write data: %s\n", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);

    return 0;
}