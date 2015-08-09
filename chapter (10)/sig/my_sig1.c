#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sig_handle(int id)
{
	printf("recieve a signal: %d\n", id);
}
int main(int argc, char* argv[])
{
	signal(SIGINT, sig_handle);
//	signal(SIGINT, SIG_IGN);
//	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig_handle);
	//signal(11, sig_handle);
	signal(9, sig_handle);
	char buf[1234] = "" ;
	read(0, buf, 1233);

	return 0 ;
}
