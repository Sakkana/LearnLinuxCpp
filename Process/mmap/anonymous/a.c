#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    char str[] = "12345";

    pid_t pid = fork();

    if(pid == 0)
        printf("son received: %s\n", str);
    else if(pid > 0)
        wait(NULL);


    return 0;
}

