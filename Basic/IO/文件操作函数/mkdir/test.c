#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buf[1024];
    char *path = getcwd(buf, sizeof(buf));

    if(path == NULL)
    {
        perror("getcwd");
        return -1;
    }

    printf("current working directory is : \n%s\n or \n%s\n", buf, path);

    int res = chdir("/home/Sakana/Mydoc/serverlearn/IO/文件操作函数/ajacentDir/");

    if(res == -1)
    {
        perror("chdir");
        return -1;
    }
    
    char newbuf[512];
    char *newPath = getcwd(newbuf, sizeof(newbuf));

    printf("\n*** change woring dir successfully! ***\n\n");
    printf("current working directory is : \n%s\n or \n%s\n", newbuf, newPath);
    
    int fd = open("testFile.txt", O_CREAT | O_RDWR, 0664);
    char pbuf[1024];
    sprintf(pbuf, "Hello, world! I'm form %s \n Here is %s\n", path, newPath);
    write(fd, pbuf, sizeof(pbuf));
    close(fd);

    return 0;
}
