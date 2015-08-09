#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char* argv[])// dirname
{
	if(mkdir(argv[1], 0777) == -1)
	{
		perror("mkdir");//mkdir:why
		exit(1);
	}
	printf("success!\n");
	return 0 ;
}

