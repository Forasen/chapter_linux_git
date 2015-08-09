#ifndef __POOL_THREAD_H__
#define __POOL_THREAD_H__
#include "pool_common.h"
#include "pool_que.h"
typedef void* (*consumer_handle)(void*) ;
typedef struct threads
{
	que_t pool_que ;
	int pool_cnt ;
	pthread_t* pool_arr ;
	consumer_handle pool_handle ;

}threadspool_t, *pthreadspool_t ;

void pool_init( pthreadspool_t ppool, int quecapacity, int threadsnum, consumer_handle hd );

void pool_on(pthreadspool_t ppool) ;

void pool_off(pthreadspool_t ppool);

void pool_put(pthreadspool_t ppool, elem_t val);

void pool_get(pthreadspool_t ppool, elem_t* val);// ok 1 no 0

void pool_destroy(pthreadspool_t ppool);
#endif
