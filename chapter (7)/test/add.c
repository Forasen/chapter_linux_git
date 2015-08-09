#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc,char* argv[])
{
	int a,b;
	char line[128];
	while(memset(line,0,128),read(0,line,127)!=0)
	{
		sscanf(line,"%d%d",&a,&b);
		memset(line,0,128);
		sprintf(line,"%d,%d+%d=%d\n",getpid(),a,b,a+b);
		write(1,line,strlen(line));
	}

	/*while(scanf("%d %d",&a,&b)!=EOF)
	{
		printf("%d,%d+%d=%d\n",getpid(),a,b,a+b);
	}*/
	return 0;
}
