#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int getFileNum(const char *path);

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("%s pathname\n", argv[1]);
		return -1;
	}

	int num = getFileNum(argv[1]);

	printf("The total num of files is: %d\n", num);

	return 0;
}

int getFileNum(const char *path)
{
	// 1. 打开目录
	DIR *dir = opendir(path);
	if(dir == NULL)
	{
		perror("opendir");
		exit(0);
	}

	// 2.记录普通文件个数
	int cnt = 0;
	struct dirent *ptr = NULL;

	while((ptr = readdir(dir)) != NULL)
	{
		// 判断是否为. 或 ..
		if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
			continue;

		// 如果是目录，需要递归计算
		if(ptr->d_type == DT_DIR)
		{
			char newpath[512];
			sprintf(newpath, "%s/%s", path, ptr->d_name);
			cnt += getFileNum(newpath);
		}
		// 如果是普通文件，计算
		if(ptr->d_type == DT_REG) ++ cnt;
	}

	// 3.关闭文件
	closedir(dir);

	return cnt;
}
