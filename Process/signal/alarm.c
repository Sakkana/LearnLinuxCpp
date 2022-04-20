#include <stdio.h>
#include <unistd.h>

int main()
{
    alarm(1);

    int cnt = 1;
    while(1)
    {
        ++ cnt;

    }

    printf("%d\n", cnt);

    return 0;
}