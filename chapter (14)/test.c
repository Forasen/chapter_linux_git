#include<stdio.h>
#define FUNC(a,b) a##b
int main(int argc, char* argv[])
{
	FUNC(1123, 3344);
	printf("int: %d\n", (int)( (int*)0 + 1 ) );
}
