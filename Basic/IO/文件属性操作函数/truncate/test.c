#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ret = truncate(argv[1], atoi(argv[2]));

    if(ret == -1)
    {
        perror("truncate");
        return -1;
    }

    printf("truncate the file %s to %s bytes successfully!\n", argv[1], argv[2]);

    return 0;
}
