#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void* thd_handle(void* arg)
{

	printf("thd: %u\n", pthread_self());
	printf("thread: %s\n", (char*)arg);
	
//	char* pstr = "how are you!\n";
	int* pint = (int*)calloc(1, 4) ;
	*pint = 1024 ;
	int fds[2] ;
	pipe(fds);
	char buf[1024] ;
	read(fds[0], buf, 1023);
//	pthread_exit((void*)pint);
	pthread_exit(NULL);


}
int main(int argc, char* argv[])
{

	pthread_t thd1, thd2, thd3 ;
	printf("main: %u\n", pthread_self());
	char* p = "hello world!\n";
	if(pthread_create(&thd1, NULL, thd_handle, (void*)p ) == -1 )
	{
		perror("pthread_create");
		exit(1);
	}
	/*
	if(pthread_create(&thd2, NULL, thd_handle, (void*)p ) == -1 )
	{
		perror("pthread_create");
		exit(1);
	}
	if(pthread_create(&thd3, NULL, thd_handle, (void*)p ) == -1 )
	{
		perror("pthread_create");
		exit(1);
	}*/

//	char* pret = NULL ;
	int* pret1 = NULL ;
	sleep(1);
	if(pthread_cancel(thd1) != 0)
	{
		printf("cancel fail!\n");
	}
//	pthread_join(thd,(void**)&pret1 );
	printf("join....!\n");
	pthread_join(thd1, NULL );
	printf("joined...!\n");
//	pthread_join(thd2, NULL );
//	pthread_join(thd3, NULL );
	//printf("main: thd ret: %d\n", *pret1);
	
	return 0 ;
}
