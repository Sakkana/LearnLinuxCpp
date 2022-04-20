#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();


    if(pid == 0)
    {

        printf("child process, pid=%d, ppid=%d\n",\
                getpid(), getppid());

    }
    else if(pid > 0)
    {
        while(1)
        {
            printf("parent process, pid=%d, ppid=%d\n",\
                getpid(), getppid());
            sleep(1);
        }

    }
    else
    {
        perror("fork");
        return -1;
    }

    for(int i = 0; i < 3; ++ i) printf("%d\n", i);

    return 0;
}
