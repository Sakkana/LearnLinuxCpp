#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    pid_t pid = fork();


    if(pid == 0)
    {
        sleep(1);

        printf("child process, pid=%d, ppid=%d\n",\
                getpid(), getppid());

        for(int i = 0; i < 3; ++ i) printf("%d\n", i);
    }
    else if(pid > 0)
    {

        printf("parent process, pid=%d, ppid=%d\n",\
                getpid(), getppid());

        for(int j = 0; j < 3; ++ j) printf("%d\n", j);
    }
    else
    {
        perror("fork");
        return -1;
    }

    return 0;
}
