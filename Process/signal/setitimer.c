#include <sys/time.h>
#include <stdio.h>

int main()
{
    /*
    struct itimerval new_value = {
        {2, 0}, // 间隔的时间（周期）
        {3, 0}  // 延迟的时间（过多久第一次执行）
    };
    */

   struct itimerval new_value;

    new_value.it_interval.tv_sec = 2;        // 周期为2s
    new_value.it_interval.tv_usec = 0;

    new_value.it_value.tv_sec = 3;          // 延迟3s后执行
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL); // 非阻塞
    if(ret == -1)
    {
        perror("setitimer");
        return -1;
    }

    printf("start timing...\n");

    getchar();  // 阻塞一下，不然还没计时3s钟就碰到return了

    return 0;
}