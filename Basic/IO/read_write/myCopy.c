#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>


int main()
{

    // 1. open ---> 打开源文件
    int srcfd = open("english.txt", O_RDONLY);

    if(srcfd == -1)
    {
        perror("open: ");
        return -1;
    }


    // 2. 创建一个新的目标文件
    int destfd = open("newEnglish.txt", O_WRONLY | O_CREAT, 0664);

    if(destfd == -1)
    {
        perror("open: ");
        return -1;
    }


    // 3. 频繁的读写操作
    char buf[1024] = {0};

    int len = 0;
    //while((len = read(srcfd, buf, sizeof(buf))) > 0)
    read(srcfd, buf, 12);
    write(destfd, buf, sizeof(buf));


    // 4. 关闭文件
    close(srcfd);
    close(destfd);

    return 0;

}
