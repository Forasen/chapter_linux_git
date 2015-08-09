#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
	char path[128] = "";
	char* p ;
	//getcwd(path, 127);
	p = getcwd(NULL, 0);
	printf("cwd: %s\n", p);
	chdir("/home");
	memset(path, 0, 128);
//	getcwd(path, 127);
	p = getcwd(NULL, 0);
	printf("cwd: %s\n", p);
	return 0 ;
}
