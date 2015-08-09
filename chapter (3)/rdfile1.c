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
int main(int argc, char* argv[])
{
	int  fd = open(argv[1], O_RDONLY);
	int readn ;
	stu_t arr[5];
	memset(arr, 0, sizeof(arr));
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	readn = read(fd, arr, sizeof(arr));
	printf("readn: %d\n", readn);
	int index ;
	for(index = 0; index < 5; index ++)
	{
		printf("%-5d%10s\n", arr[index].st_id, arr[index].st_name);
	}
	close(fd);
	return 0 ;
}
