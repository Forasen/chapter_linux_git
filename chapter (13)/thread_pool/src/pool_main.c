#include"pool_thread.h"
void* handle(void* arg)
{
	//pool_get
	//excute_task
	pthreadspool_t ppool = (pthreadspool_t)arg ;
	elem_t val ;
	while(1)
	{
		pool_get(ppool, &val);
		printf("%u: excute task !, %d + %d = %d\n", pthread_self(), val.left, val.right, val.left + val.right);
	}
}
int main(int argc, char* argv[])//capacity  num
{
	if(argc != 3)
	{
		printf("EXE QUE_CAPACITY THREADS_NUM!\n");
		exit(1);
	}
	threadspool_t mypool ;

	pool_init(&mypool, atoi(argv[1]), atoi(argv[2]), handle );

	pool_on(&mypool);

	char buf[128] ;
	while(1)
	{
		fd_set rds ;
		FD_ZERO(&rds);

		FD_SET(0, &rds);

		struct timeval tm ;
		tm.tv_sec = 1 ;
		tm.tv_usec = 0 ;

		if(0 == select(1024, &rds, NULL, NULL, &tm))
		{
			continue ;
		}
		if(FD_ISSET(0, &rds))
		{
			memset(buf, 0, sizeof(buf));
			if(read(0, buf, 127) == 0)
			{
				break ;
			}
			//init a task ;
			elem_t val ;
			sscanf(buf, "%d%d", &val.left, &val.right);
			pool_put(&mypool, val);
		}



	}

	pool_off(&mypool);

	pool_destroy(&mypool);


	return 0 ;
}
