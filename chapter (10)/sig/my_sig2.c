#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
typedef void (*pfunc_t)(int) ;

void sig_handle(int signum)
{
	printf("recieve a signal: %d\n", signum);
	if(signum == 17)
	{
		wait(NULL);
	}
	printf("%d hanlde over!\n", signum);
}
void sig_handle2(int signum, siginfo_t* pinfo, void* pvoid)
{
	printf("recieve a signal: %d\n", signum);
}

void sethandle(int signum, pfunc_t pf )
{
	struct sigaction myact;
	memset(&myact, 0, sizeof(myact));
	myact.sa_handler = pf ;
	//sigemptyset(&myact.sa_mask);
	sigfillset(&myact.sa_mask);
	myact.sa_flags = SA_RESTART  ;

	sigaction(signum, &myact, NULL);
	
}
int main(int argc, char* argv[])
{

	printf("pid: %d\n", getpid());
	sethandle(2, sig_handle);
	sethandle(3, sig_handle);
	sethandle(SIGSEGV, sig_handle);
	sethandle(SIGFPE, sig_handle);
	sethandle(SIGPIPE, sig_handle);
	sethandle(SIGCHLD, sig_handle);
	char buf[1024] = "" ;

	//segment fault
//	char* p = "hello" ;
//	*p = 'l' ;
//
//	/0
    /*
	int a  = 3 ;
	int b = 0 ;
	int c = a / b ;
	*/
	int fds[2] ;// fds[0]:r  fds[1]:w
	pipe(fds);

	if(fork() == 0)
	{
		close(fds[0]);
		close(fds[1]);
		exit(1);
	}
	close(fds[0]);
	sleep(1);

	/* sigpipe
	char* p = "hello world" ;
	write(fds[1], p, strlen(p));
	*/
	int readn = read(0, buf, 1024);
	printf("readn : %d\n", readn);
	if(readn == -1)
	{
		perror("read");
	}

	return 0 ;
}
