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


int main(int argc, char* argv[])//
{

	int semid = semget((key_t)1111, 0, 0);//0:epmty  1:full
	if(semid == -1)
	{
		perror("semget");
		exit(1);
	}


	struct sembuf myops[2] ;
	
	//empty v
	myops[0].sem_num = 0;
	myops[0].sem_op = 1;
	myops[0].sem_flg = SEM_UNDO;

	//full p
	myops[1].sem_num = 1;
	myops[1].sem_op =  -1;
	myops[1].sem_flg = SEM_UNDO;

	printf("%d: full: %d, empty: %d\n", getpid(), semctl(semid, 1, GETVAL), semctl(semid, 0, GETVAL));

	while(1)
	{
		//	p(full)
		printf("if empty!\n");
		semop(semid, &myops[1], 1);
		printf("not empty!\n");
		// v(empty)
		printf("consume a item!\n");
		semop(semid, &myops[0], 1);

		printf("%d: full: %d, empty: %d\n", getpid(), semctl(semid, 1, GETVAL), semctl(semid, 0, GETVAL));

		sleep(3);

	}

	return 0 ;
}

