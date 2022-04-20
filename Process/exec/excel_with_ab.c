#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid > 0)
    {
        printf("Parent process, pid = %d\n", getpid());
    }else if(pid == 0)
    {
        int ret = execl("~/Mydoc/serverlearn/Process/exec/hello", "hello", NULL);
        if(ret == -1)
        {
            perror("execl");
            exit(0);
        }
        printf("This might not be printed.\n");
    }

    for(int i = 0; i < 3; ++ i)
    {
        printf("i = %d, pid = %d\n", i, getpid());
    }


    return 0;
}
