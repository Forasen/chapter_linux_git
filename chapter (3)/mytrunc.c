#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc, char* argv[])// file_name
{
	int fd ;
	fd = open(argv[1], O_WRONLY);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	ftruncate(fd, 1024);

	close(fd);
}
