#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
     int fd = open("a.txt", O_RDWR);

     if(fd == -1)
     {
         perror("open : ");
         return -1;
     }

     // 扩展文件长度
     int res = lseek(fd, 0, SEEK_CUR);

     if(res == -1)
     {
         perror("lseek : ");
         return -1;
     }else
     {
         char buf[64];
         read(fd, buf, sizeof(buf) / 2);
         int res2 = lseek(fd, 0, SEEK_CUR);                                                                                                                                                                           printf("文件指针刚开始在 %d byte 处， 目前在 %d byte 处\n", res, res2);
     }

      close(fd);

      return 0;
  }
