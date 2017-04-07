#include<stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

//thread.c:(.text+0x95): undefined reference to `pthread_create' 动态库 gcc thread.c -lpthread

char buf[100];

void *func(void *arg)
{
	while(1)
	{
	memset(buf, 0, sizeof(buf));	
	read(0, buf,5 );	
	printf("键盘读出的内容是[%s]\n",buf);
	}
}
int main(void)
{
	pthread_t th = -1;				//指针指向的内存为创建线程的ID；
	int ret = -1;
	int fd = -1;

	//1.创建线程函数：
	ret = pthread_create(&th, NULL, func, NULL);  //value = 0;//依附一个进程而存在的；
	if(ret != 0)
	{
		printf("error.\n");
		return -1;
	}
	//主任务
	fd = open("/dev/input/mouse1", O_RDONLY);
	if(fd < 0)
	{
		perror("");
		return -1;
	}
	while(1)
	{
		memset(buf, 0, sizeof(buf));	
		read(fd, buf,5 );	
		printf("鼠标读出的内容是[%s]\n",buf);
	}

	//pthread_join();
	return 0;
}





