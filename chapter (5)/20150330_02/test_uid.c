#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main(int argc, char* argv[])
{

	//ppid: bash  comst: uid 500 gid:500
	//ppid: bash  
	printf("pid: %d, ppid: %d, uid: %d, gid: %d, euid: %d, egid: %d\n", getpid(), getppid(), getuid(), getgid(), geteuid(), getegid());
	//a.txt  rw--w----  root root
	//comst: open fail
	//root: open sucess
	//
	//main rwxrwxr-x root root
	//chmod a+s main  -> euid 
	//euid( == uid(运行程序的用户)) euid(chmod u+s  == owner 程序的创建者)
	//main rwsrwxr-x  
	//a.txt 
	
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	printf("%d\n", fd);
	return 0 ;
}
