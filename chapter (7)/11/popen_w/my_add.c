#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
	int left, right ;
	scanf("%d%d", &left, &right);
	printf("pid:%d %d + %d = %d\n ",getpid(), left, right, left + right);
	return 0 ;
}
