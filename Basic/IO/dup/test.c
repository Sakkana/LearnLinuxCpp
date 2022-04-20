#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main()
{
    int oldFd = open("a.txt", O_CREAT | O_RDWR, 0664);
    if(oldFd == -1)
    {
        perror("open");
        return -1;
    }

    int newFd = dup2(oldFd, 100);

    printf("oldFd: %d, newFd: %d\n", oldFd, newFd);

    close(oldFd);

    char *str = "Hello, World!\n";
    int ret = write(100, str, strlen(str));
    if(ret == -1)
    {
        perror("write");
        return -1;
    }

    close(100);

    return 0;
}
