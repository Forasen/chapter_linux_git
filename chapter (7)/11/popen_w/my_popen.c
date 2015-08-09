#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
	int left, right ;
	while(scanf("%d%d", &left, &right) != EOF)
	{
		FILE* fp = popen("./my_add", "w") ;

		fprintf(fp, "%d %d\n", left, right);

		pclose(fp);
	}
	return 0 ;
}
