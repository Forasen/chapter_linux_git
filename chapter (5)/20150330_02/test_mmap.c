#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
typedef struct stu
{
	int st_id;
	char st_name[20];
	int st_age;
}stu_t, *pstu_t;
void readfile(char* path);
int main(int argc, char* argv[])//file_name
{
	readfile(argv[1]);
	int fd = open(argv[1], O_RDWR);
	struct stat mystat ;
	memset(&mystat, 0, sizeof(mystat));

	if(-1 == lstat(argv[1], &mystat ))
	{
		perror("stat");
		exit(1);
	}

	pstu_t parr = mmap(NULL, mystat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(parr == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}
	strcpy(parr[1].st_name, "li4");
	parr[4].st_age = -18 ;

	msync(parr, mystat.st_size, 0);
	munmap(parr, mystat.st_size);

	readfile(argv[1]);
	return 0 ;
}
/*
void test1()
{
	int fd = open(argv[1], O_RDONLY);
	struct stat mystat ;
	memset(&mystat, 0, sizeof(mystat));

	if(-1 == lstat(argv[1], &mystat ))
	{
		perror("stat");
		exit(1);
	}


	char* pcontent = mmap(NULL, mystat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0 );
	if(pcontent == MAP_FAILED)
	{
		perror("mmap:");
		close(fd) ;
		exit(1);
	}

	printf("%s\n", pcontent);

	munmap(pcontent, mystat.st_size);

} 

void test2()
{
	stu_t arr[5] = {{1001, "zhangsan", 17}, {1002, "li4", 18 }, {1003, "wangwu", 19}, {1004, "zhaoliu", 20}, {1007, "wangba", -18}};
	int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);

	write(fd, arr, sizeof(arr));
	close(fd);
}*/
void readfile(char* path)
{
	int fd = open(path, O_RDONLY);
	stu_t arr[5] ;
	memset(arr, 0, sizeof(arr));

	read(fd, arr, sizeof(arr));

	int i ;
	for(i = 0; i < 5; i ++)
	{
		printf("%-5d%10s%5d\n", arr[i].st_id, arr[i].st_name, arr[i].st_age);
	}
	close(fd);


}
