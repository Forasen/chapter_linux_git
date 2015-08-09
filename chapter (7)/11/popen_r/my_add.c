#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(int argc, char* argv[])// left right
{
	int left, right ;
	left = atoi(argv[1]);
	right = atoi(argv[2]);
	printf("pid: %d, %d + %d = %d\n",getpid(), left, right, left + right);
	return 0 ;
}
