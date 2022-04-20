#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    // 先判断管道文件是否存在，若不存在，创建
    int ret = access("myfifo", F_OK);

    if(ret == -1)
    {
        printf("管道不存在，正在为您创建...\n");

        int ret = mkfifo("myfifo", 0664);
        if(ret == -1)
        {
            perror("mkfifo");
            return -1;
        }
    }else
        printf("管道已存在\n");

    return 0;
}