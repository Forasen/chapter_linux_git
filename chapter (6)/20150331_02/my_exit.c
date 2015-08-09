#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(int argc, char* argv[] )
{
	pid_t pid ;
	pid = fork() ;
	if(pid == 0)
	{
		printf("child: %d\n", getpid());
		sleep(8);
		exit(1);
	}else if(pid > 0)
	{
		pid_t pid2 = fork();
		if(pid2 == 0)
		{
			printf("child: %d\n", getpid());
			sleep(5);
			exit(3);
		}else if(pid2 > 0)
		{
			printf("parent: %d\n", getpid());
			int ret ;
			pid_t child_pid ;
			printf("waiting......!\n");
			child_pid = wait(&ret);
			wait(NULL) ;
			printf("%d exit: %04x\n", child_pid, ret);
			while(1);
		}

	}
	return 0 ;
}
void test()
{
	pid_t pid ;
	int cnt = 0 ;
	while(1)
	{
		cnt ++ ;
		pid = fork() ;
		if(pid == -1)
		{
			perror("fork");
			break ;
		}
		if(pid == 0)
		{
			exit(1);
		}else 
		{
			if(cnt % 50 == 0)
			{
				sleep(1);
			}
			wait(NULL);
			continue ;
		}

	}

}
