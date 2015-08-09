#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
extern char** environ ;// = {"","", "", NULL}
void test();
int main(int argc, char** argv)
{
	char* myenv[] = {"NAME=zhangsan", "AGE=18", NULL};
	printf("my_exec: %d\n", getpid());
	printf("------------------------\n");
//	execl("/bin/ls", "ls", "-l", NULL);
//	execlp("/bin/ls", "ls", "-l", NULL);
//	execl("./my_add","./my_add", "1", "3", NULL );
//execlp("./my_add","./my_add", "1", "3", NULL );
//	test();
//	execle("./my_add", "./my_add", "1", "3", NULL, myenv);
//	char* pwd = getenv("PWD");
//	printf("pwd: %s\n", pwd);
	
	char* arglist[] = {"./my_add", "1", "3", NULL};
	//execv(arglist[0], arglist );
//	execvp(arglist[0], arglist );
	execve(arglist[0], arglist, myenv );
	printf("++++++++++++++++++++++++++\n");
	return 0 ;
}
void test()
{
	int index ;
	for(index = 0; environ[index] != NULL; index ++)
	{
		printf("%d: %s\n", index, environ[index]);
	}
}
