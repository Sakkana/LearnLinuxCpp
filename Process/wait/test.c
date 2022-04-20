#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    for(int i = 0; i < 5; ++ i)
    {
        pid = fork();
        if(pid == 0)
            break;
    }

    
    if(pid == 0)
    {
        printf("I'm son, pid=%d\n", getpid());
        sleep(1);

        printf("son pid=%s died\n", getpid());
        exit(0); 
    }else if(pid > 0)
    {
        while (1)
        {
            printf("I'm parent, pid=%d\n", getpid());
            sleep(1);
        }
    }else
    {
        perror("fork");
        return -1;
    }


    return 0;
}