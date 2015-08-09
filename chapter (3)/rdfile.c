#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
	int  fd = open(argv[1], O_RDONLY);
	int readn ;
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	char buf[1024] = "" ;

	while( memset(buf, 0, 1024), (readn = read(fd, buf, 1023) ) > 0 )
	{
		printf("read: %s\n", buf);
		printf("readn: %d\n", readn);
	}
	
	close(fd);
	printf("over!\n");
	return 0 ;
}
