#include"pool_thread.h"

void pool_init( pthreadspool_t ppool, int quecapacity, int threadsnum, consumer_handle hd )
{
	que_init( &ppool ->pool_que,quecapacity );

	ppool->pool_arr = (pthread_t*)calloc(threadsnum, sizeof(pthread_t));
	ppool->pool_cnt = threadsnum ;

	ppool ->pool_handle = hd ;


}

void pool_on(pthreadspool_t ppool)
{
		int index ;
		for(index = 0; index < ppool ->pool_cnt; index ++)
		{
			if(0 != pthread_create(ppool ->pool_arr + index, NULL, ppool ->pool_handle, (void*)ppool  ))
			{
				printf("thread create fail !\n");
				exit(1);
			}
		}

}

void pool_off(pthreadspool_t ppool)
{
	//
	//

	int index ;
	for(index = 0; index < ppool ->pool_cnt; index ++)
	{
		pthread_join(ppool ->pool_arr[index], NULL) ;
	}

}


void pool_put(pthreadspool_t ppool, elem_t val)
{
	que_push( &ppool ->pool_que, val ) ;
}

void pool_get(pthreadspool_t ppool, elem_t* val)
{
	//atomically 
	
	*val = que_top(&ppool ->pool_que);
	que_pop(&ppool ->pool_que);
}

void pool_destroy(pthreadspool_t ppool)
{
	que_destroy( &ppool ->pool_que);
	free(ppool ->pool_arr);
}
