#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        printf("child process, return value=%d, pid=%d, ppid=%d\n",\
                pid, getpid(), getppid());
    }
    else if(pid > 0)
    {
        printf("parent process, return value=%d, pid=%d, ppid=%d\n",\
                pid, getpid(), getppid());
    }
    else
    {
        perror("fork");
        return -1;
    }

    for(int i = 1; i <= 1000; ++ i)
    {
        printf("%d, pid = %d\n", i, getpid());
        //sleep(1);
    }

    return 0;
}
