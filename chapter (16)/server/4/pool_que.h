#ifndef __QUE__
#define __QUE__
#include "pool_common.h"
typedef enum
{
	EMPTY, FULL, NEITHER
}STATUS ;
typedef struct  que
{
	elem_t* que_arr ;
	int que_front ;
	int que_tail ;
	int que_capacity ;
	pthread_mutex_t que_lock;
	pthread_cond_t que_pro;// que full
	pthread_cond_t que_con;// que empty
}que_t, *pque_t;

void que_init(pque_t pq, int sizenum) ;

STATUS que_empty(pque_t pq);

STATUS que_full(pque_t pq);

void que_push(pque_t pq, elem_t val);

void que_pop(pque_t pq);

elem_t que_top(pque_t pq);

void que_destroy(pque_t pq);
#endif
