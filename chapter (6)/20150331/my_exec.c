#include<stdio.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
	printf("my_exec: %d\n", getpid());
	printf("------------------------\n");
//	execl("/bin/ls", "ls", "-l", NULL);
	execl("./my_add","./my_add", "1", "3", NULL );
	printf("++++++++++++++++++++++++++\n");
	return 0 ;
}
