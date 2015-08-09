#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(int argc, char* argv[])
{
	int fds0[2];// p -> c
	int fds1[2];// c -> p
	if(pipe(fds0) == -1 || pipe(fds1) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid_t pid ;
	pid = fork();
	if(pid >  0)
	{
		close(fds0[0]);
		close(fds1[1]);
		int left, right ;
		char msg[128];
		while(scanf("%d%d", &left, &right) != EOF)
		{
			memset(msg, 0, sizeof(msg));
			sprintf(msg, "%d %d\n", left, right);
			write(fds0[1], msg, strlen(msg));

			memset(msg, 0, sizeof(msg));
			read(fds1[0], msg, 127);
			printf("%s\n", msg);
		}
	}else if(pid == 0)
	{
		close(fds0[1]);
		close(fds1[0]);

		dup2(fds0[0], 0);
		dup2(fds1[1], 1);

		if(execl("./my_add", "./my_add", NULL) == -1)
		{
			perror("execl");
			exit(1);
		}



	}

	return 0; 
}
