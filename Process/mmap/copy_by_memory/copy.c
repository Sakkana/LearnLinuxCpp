#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    // 1. 打开源文件
    int fdSrc = open("src.txt", O_RDWR);
    if(fdSrc == -1)
    {
        perror("open_src");
        return -1;
    }

    // 获取源文件大小
    int srcSize = lseek(fdSrc, 0, SEEK_END);
    if(srcSize == -1)
    {
        perror("lseek");
        return -1;
    }

    // 2. 创建新文件
    int fdDest = open("dest.txt", O_RDWR | O_CREAT, 0664);
    if(fdDest == -1)
    {
        perror("open_dest");
        return -1;
    }

    // 3. 扩展新文件
    truncate("dest.txt", srcSize);
    write(fdDest, "", 1);

    // 4. 分别做内存映射
    void *ptrSrc = mmap(NULL, srcSize + 1, PROT_READ | PROT_WRITE, MAP_SHARED, fdSrc, 0);
    if(ptrSrc == MAP_FAILED)
    {
        perror("mmap_src");
        return -1;
    }

    void *ptrDest = mmap(NULL, srcSize + 1, PROT_READ | PROT_WRITE, MAP_SHARED, fdDest, 0);
    if(ptrDest == MAP_FAILED)
    {
        perror("mmap_dest");
        return -1;
    }
    

    // 5. 内存拷贝
    /*
    这个不是内存拷贝，这个是文件IO里学的文件拷贝
    char buf[1024] = {0};
    int len = 0;
    while(len = (read(fdSrc, buf, sizeof(buf))) > 0)
        write(fdDest, buf, len);

    */

    memcpy(ptrDest, ptrSrc, srcSize);

    // 6. 释放资源
    munmap(ptrSrc, srcSize + 1);
    munmap(ptrDest, srcSize + 1);

    close(fdDest);
    close(fdSrc);   // 由于依赖关系也要注意先后释放顺序，虽然我没听懂
    

    return 0;
}