#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void getMemery(char** p);
int main(int argc, char* argv[])
{
	char* pstr = NULL ;
	getMemery(&pstr) ;

	strcpy(pstr,  "hello world");
	printf("%s\n", pstr);
	return 0 ;
}
void getMemery(char** p)
{
	*p = (char*) calloc(20, 1);

	strcpy(*p, "abcdefg");
}
