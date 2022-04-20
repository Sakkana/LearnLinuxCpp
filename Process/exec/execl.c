#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();

    if(pid > 0)
    {
        printf("Parent process, pid = %d\n", getpid());
        sleep(1);
    }else if(pid == 0)
    {
        int ret = execl("hello", "hello", "aux", NULL);
        if(ret == -1) perror("execl");
        printf("This might not be printed.\n");
    }

    for(int i = 0; i < 3; ++ i)
    {
        printf("i = %d, pid = %d\n", i, getpid());
    }


    return 0;
}
