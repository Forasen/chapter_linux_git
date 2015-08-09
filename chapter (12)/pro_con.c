#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
int cnt ;
typedef struct tag
{
	int g_i ;
	pthread_cond_t cond1,cond2; //cond1-seller  cond2 -another
	pthread_mutex_t lock;
}NODE, *pNODE ;
void* get_handle(void* arg)
{
	pNODE p = (pNODE)arg ;
	int tmp ;

	while(1)
	{
		pthread_mutex_lock( &p ->lock);
		while(p ->g_i == 0)
		{
			pthread_cond_signal(&p ->cond2);
			//1. unlock 
			//2. block   g_i = 1;
			//3  block ->unblock
			//           g_i = 0 ;
			//4  lock
			//5 retur
			pthread_cond_wait(&p ->co<F12>nd1, &p ->lock);
		}
		/* busy waitting
		   if(p ->g_i <= 0)
		   {

		   pthread_mutex_unlock(&p ->lock);
		   sleep(rand() % 5 + 1);
		   continue ;

		   }*/


		tmp = p ->g_i ;
		printf("%u: sell a ticket: %d\n",pthread_self(), tmp );
		cnt ++ ;

		p->g_i -- ;

		pthread_mutex_unlock(&p ->lock);
		//	cnt -- ;
	}

}
void* put_handle(void* arg)
{
	pNODE p = (pNODE)arg ;
	while(1)
	{
		//wait
		pthread_mutex_lock(&p ->lock);
		while(p ->g_i > 0)
		{
			pthread_cond_wait(&p ->cond2, &p ->lock);
		}
		p ->g_i += 5 ;
		printf("ticket on! : %d\n", p ->g_i);

		pthread_cond_signal(&p ->cond1);

		pthread_mutex_unlock(&p ->lock);

		/*  busy waitting
			pthread_mutex_lock(&anode.lock);
			if(anode.g_i <= 0)
			{
			anode.g_i = 5 ;
			printf("ticket on!\n");
			}
			pthread_mutex_unlock(&anode.lock);
		//		sleep(rand() % 5 + 1);*/
	}

}
int main(int argc, char* argv[])//m-get   n-put 
{

	NODE anode ;
	memset(&anode, 0, sizeof(anode));

	anode.g_i = 0 ;

	pthread_t thd1, thd2, thd3 ;
	int m = atoi(argv[1]);//getter
	int n = atoi(argv[2]);//putter
	pthread_t* arr = (pthread_t*)calloc(m + n, sizeof(pthread_t));
	int index = 0 ;

	if(0 != pthread_mutex_init(&anode.lock, NULL) )
	{
		printf("mutex_init fail!\n");
		exit(1);
	}
	if(0 != pthread_cond_init(&anode.cond1, NULL))
	{
		printf("cond1 init!");
		exit(0);
	}
	if(0 != pthread_cond_init(&anode.cond2, NULL))
	{
		printf("cond2 init!");
		exit(0);
	}

	while(m)
	{
		if(pthread_create( &arr[index], NULL, get_handle, (void*)&anode ) != 0)
		{
			printf("pthread_create fail!\n");
			exit(-1);
		}
		index ++ ;
		m -- ;
	}
	while(n)
	{
		if(pthread_create( &arr[index], NULL, put_handle, (void*)&anode ) != 0)
		{
			printf("pthread_create fail!\n");
			exit(-1);
		}
		index ++ ;
		n -- ;
	
	}

	index-- ;
	while(index)
	{
		pthread_join(arr[index], NULL);
		index -- ;
	}

	pthread_mutex_destroy(&anode.lock);
	pthread_cond_destroy(&anode.cond1);
	pthread_cond_destroy(&anode.cond2);
	printf("cnt: %d\n", cnt);
	return 0;
}
