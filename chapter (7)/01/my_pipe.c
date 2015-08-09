#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(int argc, char* argv[])
{
	int fds[2] ;//fds[1]  fds[0]
	if(-1 == pipe(fds))
	{
		perror("pipe");
		exit(1);
	}
	pid_t pid ;
	pid = fork() ;
	if(pid == 0)// recv
	{
		printf("child: fds[1]: %d, fds[1]: %d\n", fds[0], fds[1]);
		char buf[1024] = "" ;
		close(fds[1]);
		while(memset(buf, 0, 1024), read(fds[0], buf, 1023) != 0)
		{
			printf("from parent: %s\n", buf);
		}
		close(fds[0]);
		exit(1);
		
	}else //send
	{
		printf("parent: fds[1]: %d, fds[1]: %d\n", fds[0], fds[1]);
		char buf[1024] = "" ;
		close(fds[0]);

		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL)
		{
			write(fds[1], buf, strlen(buf));
		}
		close(fds[1]);
		printf("waiting...!\n");
		wait(NULL);
		printf("wait ret!\n");
	}
	return 0 ;
}
