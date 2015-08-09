#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
int main(int argc, char* argv[])
{
	time_t tm ;
	time(&tm);
	int val ;
	printf("----\n");
	scanf("%d", &val);
	printf("-----\n");
	printf("%s\n", ctime(&tm));
	double* p = calloc(1, 4);

	*p = 3.14 ;

	printf("%f\n",*p );

	return 0 ;
}
