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
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	stu_t stu = {0, ""} ;
	lseek(fd, 2 * sizeof(stu_t), SEEK_SET);

	read(fd, &stu, sizeof(stu));

	printf("id: %d, name: %s\n", stu.st_id, stu.st_name);
	close(fd);
}
