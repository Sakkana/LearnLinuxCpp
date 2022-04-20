#include <stdio.h>
#include <sys/stat.h>

int main()
{
    int ret = chmod("a.txt", 0000);
    
    if(ret == -1)
    {
        perror("chmod");
        return -1;
    }

    printf("change mode successfully!\n");

    return 0;
}
