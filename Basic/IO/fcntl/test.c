#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main()
{
    // 打开文件
    int fd = open("a.txt", O_RDWR | O_CREAT, 0664);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }

    // 获取文件状态 flag
    int flag = fcntl(fd, F_GETFL);
    if(flag == -1)
    {
        perror("fcntl");
        return -1;
    }

    // 设置文件状态 flag
    flag |= O_APPEND;
    int ret = fcntl(fd, F_SETFL, flag);
    if(ret == -1)
    {
        perror("fcntl");
        return -1;
    }

    char *str = "Hello, fcntl\n";
    write(fd, str, strlen(str));

    close(fd);


    return 0;
}
