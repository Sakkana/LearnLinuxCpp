#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    struct stat statbuf;

    int res = stat("a.txt", &statbuf);

    if(res == -1)
    {
        perror("stat : ");
        return -1;
    }

    printf("该文件对于当前用户是否可写可读可执行？: %o\n", statbuf.st_mode & S_IRWXU);

    return 0;
}
