#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    // 1.直接打开管道
    int fd = open("myfifo", O_RDONLY);
       if(fd == -1)
       {
           perror("open");
           exit(0);
       }

       // 2.读数据
       char buf[1024];
       while(1)
       {
           // read返回读到的字节数
           // read失败返回 -1
           // 写端关闭，管道中数据读完，返回0
           int len = read(fd, buf, sizeof(buf));
            if(len == 0)
            {
                printf("写端断开连接\n");
                break;
            }
            printf("receive buf: %d\n", len);
       }

        close(fd);

    return 0;
}