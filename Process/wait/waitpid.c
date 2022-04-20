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
        while(1)
        {
            printf("I'm son, pid=%d\n", getpid());
            sleep(1);
        }
        printf("child %d died\n", getpid());
        exit(0); 
    }else if(pid > 0)
    {
        while (1)
        {
            sleep(1);
            printf("I'm parent, pid=%d\n", getpid());

            int st;
            int ret = waitpid(-1, &st, WNOHANG); 
            if(ret == -1) break;
            if(ret == 0) continue;

            if(WIFEXITED(st)) printf("child died peacefully, status:%d\n", WEXITSTATUS(st));        // 正常中止
            if(WIFSIGNALED(st)) printf("child was killed by signal %d\n", WTERMSIG(st));      // 被信号中止

            
        }
    }else
    {
        perror("fork");
        return -1;
    }


    return 0;
}
