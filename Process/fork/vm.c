#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int global_a = 0;

int main()
{
    int local_a = 99;

    pid_t pid = fork();

    int after_fork_a = 999;

    printf("Before: global_a=%d, local_a=%d, after_fork_a=%d\n",\
            global_a, local_a, after_fork_a);

    if(pid == 0)
    {
        printf("child process, return value=%d, pid=%d, ppid=%d\n",\
                pid, getpid(), getppid());
        ++ global_a, ++ local_a, ++ after_fork_a;
        printf("global_a=%d, local_a=%d, after_fork_a=%d\n",
                global_a, local_a, after_fork_a);
    }
    else if(pid > 0)
    {
        printf("parent process, return value=%d, pid=%d, ppid=%d\n",\
                pid, getpid(), getppid());
        -- global_a, -- local_a, -- after_fork_a;
        printf("global_a=%d, local_a=%d, after_fork_a=%d\n",
                global_a, local_a, after_fork_a);
    }
    else
    {
        perror("fork");
        return -1;
    }

    return 0;
}
