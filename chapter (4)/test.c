#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char* argv[])
{
	char buf[1024] = "" ;
	//stdin 0
	read(0, buf, 1023 );
	write(1, buf, strlen(buf));
	return 0 ;
}
