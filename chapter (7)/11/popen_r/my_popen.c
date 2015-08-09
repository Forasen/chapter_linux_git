#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
	int left, right ;
	char line[1024];
	char cmd[128] ;
	printf("popen pid: %d\n", getpid() );
	while(scanf("%d%d", &left, &right) != EOF)
	{
		memset(cmd, 0, 128);
		sprintf(cmd, "%s %d %d", "./my_add", left, right);
		printf("cmd: %s\n", cmd);
		FILE* fp = popen(cmd, "r" );
		if(fp == NULL)
		{
			perror("popen");
			exit(1);
		}
		memset(line, 0, 1024);
		fgets(line, 1024, fp);
		write(1, line, strlen(line));
		pclose(fp);

		
	}
	return 0 ;
}	
