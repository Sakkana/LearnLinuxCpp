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
        char *argv[5];
        argv[0] = "hello";
        argv[1] = NULL;

        char *env[] = {"PATH=/home/Sakana/Mydoc/serverlearn/Process", (char*)0};

        int ret = execve("hello", argv, env);

        if(ret == -1) perror("execl");

        printf("This might not be printed.\n");
    }

    for(int i = 0; i < 3; ++ i)
    {
        printf("i = %d, pid = %d\n", i, getpid());
    }


    return 0;
}
