#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc,char *argv[])
{
	int fds[2];
	if(pipe(fds)==-1)
	{
		perror("pipe");
		exit(1);
	}
		pid_t pid;
	pid=fork();
	while(1){
	if(pid==0)
	{
		printf("%d,%d",fds[0],fds[1]);
	//	close(fds[1]);
		char buf[1024];
		memset(buf,0,1024);
		while(memset(buf,0,1024),read(fds[0],buf,1023)!=0)
		{
			printf("from parent:%s\n",buf);
		}
		close(fds[0]);
		close(fds[1]);
		exit(1);
	//	read(fds[0],buf,1023);
	//	printf("%s\n",buf);
	//	memset(buf,0,1024);

	//	read(fds[0],buf,1023);
	//	printf("%s\n",buf);
	//	close(fds[0]);
	//	exit(1);
	}
	else
	{
		printf("%d,%d",fds[0],fds[1]);
		char buf1[1024];
	//	close(fds[0]);
        while(memset(buf1,0,1024),fgets(buf1,1024,stdin)!=NULL)
		{
			write(fds[1],buf1,strlen(buf));
		}
		char *p="hello world";
	//	write(fds[1],p,strlen(p));
	//	write(fds[1],p,strlen(p));
	    
		wait(NULL);
		close(fds[1]);
	}
	}
return 0;
}
