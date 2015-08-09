#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
								(Linux-specific) */
};


int main(int argc, char* argv[])// capacity
{
	int capacity = atoi(argv[1]);

	int semid = semget((key_t)1111, 2, IPC_CREAT | 0666);//0:epmty  1:full
	if(semid == -1)
	{
		perror("semget");
		exit(1);
	}

	unsigned short myarr[] = {capacity, 0};

	union semun mysem ;
	mysem.array = myarr ;

	semctl(semid, 0, SETALL, mysem);

	struct sembuf myops[2] ;
	
	//empty p
	myops[0].sem_num = 0;
	myops[0].sem_op = -1;
	myops[0].sem_flg = SEM_UNDO;

	//full v
	myops[1].sem_num = 1;
	myops[1].sem_op =  1;
	myops[1].sem_flg = SEM_UNDO;

	printf("%d: full: %d, empty: %d\n", getpid(), semctl(semid, 1, GETVAL), semctl(semid, 0, GETVAL));

	while(1)
	{
		//	p(empty)
		printf("if full!\n");
		semop(semid, &myops[0], 1);
		printf("not full!\n");
		// v(full)
		printf("produce a item!\n");
		semop(semid, &myops[1], 1);

		printf("%d: full: %d, empty: %d\n", getpid(), semctl(semid, 1, GETVAL), semctl(semid, 0, GETVAL));

		sleep(1);

	}

	return 0 ;
}

