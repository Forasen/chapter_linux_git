#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
	char path[128] = "";
	getcwd(path, 127);
	printf("cwd: %s\n", path);
	chdir("/home");
	memset(path, 0, 128);
	getcwd(path, 127);
	printf("cwd: %s\n", path);
	return 0 ;
}
