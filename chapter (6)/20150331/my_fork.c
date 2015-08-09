#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main(int argc, char* argv[])
{
	printf("before fork!\n");
	int a = 1024 ;
	int fd = open("./my_fork.c", O_RDONLY);
	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if(pid == 0)//child
	{
		sleep(1);
		char buf[1024] = "" ;
		read(fd, buf, 1023);
//		printf("%s\n", buf);
		printf("child: pid: %d ppid: %d fork_ret: %d, a: %d\n", getpid(), getppid(), pid, a);

		printf("child exit!\n");
		exit(1);
	}else // parent
	{
		close(fd);
		a ++ ;
		printf("parent: pid: %d ppid: %d fork_ret: %d, a: %d\n", getpid(), getppid(), pid, a);
		printf("parent exit!\n");
		sleep(10);
		exit(1);
		
	}

	return 0 ;
}
