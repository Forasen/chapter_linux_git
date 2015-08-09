#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void func()
{
	printf("func!\n");
}
int main(int argc, char* argv[])
{
	atexit(&func);
//	abort();
	while(1);
	printf("hello world");
//	exit(1);
	_exit(1);
}
