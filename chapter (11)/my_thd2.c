#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
int cnt ;
typedef struct tag
{
	int g_i ;
	pthread_mutex_t lock;
}NODE, *pNODE ;
void* thd_handle(void* arg)
{
	pNODE p = (pNODE)arg ;
	int tmp ;

	while(1)
	{
		pthread_mutex_lock( &p ->lock);
		
		if(p ->g_i <= 0)
		{
				
			pthread_mutex_unlock(&p ->lock);
			sleep(rand() % 5 + 1);
			continue ;

		}


		tmp = p ->g_i ;
		sleep(rand()%3 + 1);
		printf("%u: sell a ticket: %d\n",pthread_self(), tmp );
		cnt ++ ;

		p->g_i -- ;
	
		pthread_mutex_unlock(&p ->lock);
		sleep(rand()%2 + 1);
	//	cnt -- ;
	}

}
int main(int argc, char* argv[])
{

	NODE anode ;
	memset(&anode, 0, sizeof(anode));

	anode.g_i = 10 ;
	
	pthread_t thd1, thd2, thd3 ;

	pthread_mutex_t mylock ;
	if(0 != pthread_mutex_init(&anode.lock, NULL) )
	{
		printf("mutex_init fail!\n");
		exit(1);
	}

	if(pthread_create(&thd1, NULL, thd_handle, (void*)&anode ) != 0)
	{
		printf("pthread_create fail!\n");
		exit(-1);
	}

	if(pthread_create(&thd2, NULL, thd_handle, (void*)&anode ) != 0)
	{
		printf("pthread_create fail!\n");
		exit(-1);
	}

	if(pthread_create(&thd3, NULL, thd_handle, (void*)&anode ) != 0)
	{
		printf("pthread_create fail!\n");
		exit(-1);
	}

	while(1)
	{
		pthread_mutex_lock(&anode.lock);
		if(anode.g_i <= 0)
		{
			anode.g_i = 5 ;
			printf("ticket on!\n");
		}
		pthread_mutex_unlock(&anode.lock);
//		sleep(rand() % 5 + 1);
	}
	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);
	pthread_join(thd3, NULL);
	
	pthread_mutex_destroy(&anode.lock);
	printf("cnt: %d\n", cnt);
	return 0;
}
