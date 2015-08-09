#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(int argc,char *argv[])
{
	int fds0[2];
	int fds1[2];
	if(pipe(fds0)==-1||pipe(fds1)==-1)
	{
		perror("pipe");
		exit(1);
	}
	pid_t pid;
	pid=fork();
	if(pid>0)
	{
		int a,b;
		close(fds0[0]);
		close(fds1[1]);
		char buf[128];
		while(scanf("%d%d",&a,&b)!=EOF)
		{
			memset(buf,0,sizeof(buf));
			sprintf(buf,"%d %d\n",a,b);
			write(fds0[1],buf,strlen(buf));

			memset(buf,0,sizeof(buf));
			read(fds1[0],buf,127);
			printf("%s\n",buf);
		}
	}
	else if(pid==0)
	{

		close(fds0[1]);
		close(fds1[0]);
		dup2(fds0[0],0);
		dup2(fds1[1],1);

		if(execl("./add","./add",NULL)==-1)
		{
			perror("execl");
			exit(1);
		}


	}

	return 0;
}
