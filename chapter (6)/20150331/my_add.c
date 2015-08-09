#include<stdio.h>
#include<unistd.h>
int main(int argc, char* argv[])//left right
{
	int left = atoi(argv[1]) ;
	int right = atoi(argv[2]);
	printf("my_add: pid: %d\n", getpid());
	printf("%d + %d = %d\n", left, right, left + right);
	return left + right ;

}
