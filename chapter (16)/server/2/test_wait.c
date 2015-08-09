#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
int cnt = 0 ;
void handle(int num)
{
	int i = 10000000;
	while(i >0)
	{
		i -- ;
	}
	while(waitpid(-1, NULL, WNOHANG) > 0) ;
	cnt ++ ;
	printf("a child exit: %d\n", cnt);
}
int main(int argc, char* argv[])
{
	signal(SIGCHLD, handle);
	int n = 10 ;
	while(n > 0)
	{
		if(fork() == 0)
		{
			exit(1);
		}
		n -- ;
	}
	while(1);

	return 0 ;
}
