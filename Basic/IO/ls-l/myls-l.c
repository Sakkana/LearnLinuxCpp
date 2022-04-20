#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h> // getpwduid()
#include <grp.h> // getgrgid()
#include <time.h> // 秒数 ---> 本地时间
#include <string.h>

// 最终效果 -rw-rw-r-- 1 Sakana Sakana 137 Apr 11 15:56 nyls-l.c
// 权限 硬链接数 所有者 所在组 大小 修改时间 文件名

int main(int argc, char *argv[])
{
    // 一般会有两个参数， argv[0] = 文件名称, argv[1] = 第一个传入参数名称
    if(argc < 2)
    {
        printf("format: %s filename\n", argv[0]);
        return -1;
    }

    // 查找文件信息
    struct stat statbuf;
    int ret = stat(argv[1], &statbuf);
    
    if(ret == -1)
    {
        perror("stat: ");
        return -1;
    }

    // 获取文件类型
    char permissions[11] = {0};

    // 用st_mode中的16位整数值和掩码做按位与 (st_mode & S_IFMT) == ?
    switch(statbuf.st_mode & S_IFMT)
    {
    case S_IFSOCK:	// 套接字
        permissions[0] = 's';
		break;
	case S_IFLNK:	// 软链接
		permissions[0] = 'l';
		break;
	case S_IFREG:	// 普通文件
		permissions[0] = '-';
		break;
	case S_IFBLK:	// 块设备
		permissions[0] = 'b';
		break;
	case S_IFDIR:	// 目录
		permissions[0] = 'd';
		break;
	case S_IFCHR:	// 字符设备
		permissions[0] = 'c';
		break;
	case S_IFIFO:	// 管道
		permissions[0] = 'p';
		break;
    default:
		permissions[0] = '?';
		break;
    }
	
	// 获取访问权限
    //
	// 所有者
	permissions[1] = statbuf.st_mode & S_IRUSR ? 'r' : '-';
	permissions[2] = statbuf.st_mode & S_IWUSR ? 'w' : '-';
	permissions[3] = statbuf.st_mode & S_IXUSR ? 'x' : '-';
	
	// 文件所在组
	permissions[4] = statbuf.st_mode & S_IRGRP ? 'r' : '-';
	permissions[5] = statbuf.st_mode & S_IWGRP ? 'w' : '-';
	permissions[6] = statbuf.st_mode & S_IXGRP ? 'x' : '-';
	
	// 其他用户
	permissions[7] = statbuf.st_mode & S_IROTH ? 'r' : '-';
	permissions[8] = statbuf.st_mode & S_IWOTH ? 'w' : '-';
	permissions[9] = statbuf.st_mode & S_IXOTH ? 'x' : '-';
	

    // 硬链接数
    int linkNum = statbuf.st_nlink;

    // 文件所有者
    char *fileUsr = getpwuid(statbuf.st_uid) -> pw_name;  // uid是文件所有者的ID， 函数返回所有者的名称

    // 文件所在组
    char *fileGrp = getgrgid(statbuf.st_gid) -> gr_name;

    // 文件大小
    long int fileSize = statbuf.st_size;

    // 获取修改的时间
    // st_time 是一个 long int 类型的秒数
    char *time = ctime(&statbuf.st_mtime);

    time[strlen(time) - 1] = '\0';
    


    // 输出 -rw-rw-r-- 1 Sakana Sakana 137 Apr 11 15:56 nyls-l.c
    char buf[1024];
    sprintf(buf, "%s %d %s %s %ld %s %s", permissions, linkNum, fileUsr, fileGrp, fileSize, time, argv[0]);
    printf("%s\n", buf);

    return 0;
}
