#include <stdio.h>
//#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int ret = chown("a.txt", 1001, 1002);

    if(ret == -1)
    {
        perror("chown");
        return -1;
    }

    printf("change uid and group successfully!\n");

    return 0;
}

