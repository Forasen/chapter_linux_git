#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
typedef struct stu
{
	int st_id ;
	char st_name[20];
	
}stu_t, *pstu_t;
int main(int argc, char* argv[])// file_name
{
	int fd ;
	fd = open(argv[1], O_WRONLY | O_CREAT, 0666);

	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	stu_t astu ;
	while(memset(&astu, 0, sizeof(astu)), fscanf(stdin, "%d%s", &astu.st_id, astu.st_name) != -1)
	{
		write(fd, &astu, sizeof(astu) );
	}
	close(fd);
	return 0 ;
}
