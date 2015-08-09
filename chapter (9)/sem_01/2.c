#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/sem.h>
union semun 
{
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
								(Linux-specific) */
};
int main(int argc, char* argv[])
{
	//sem
	struct sembuf myop ;
	int semid = semget((key_t)1234, 1, 0);
	if(semid == -1)
	{
		perror("semid");
		exit(1);
	}


	//shm
	int shmid = shmget((key_t)1024, 4, 0);
	if(shmid == -1)
	{
		perror("shm");
		exit(1);
	}
	int* p =(int*)shmat(shmid, NULL, 0);

	int cnt = atoi(argv[1]); ;
	while(cnt > 0)
	{
		cnt -- ;
		
		memset(&myop, 0, sizeof(myop));

		myop.sem_num = 0 ;
		myop.sem_op = -1 ;
		myop.sem_flg = SEM_UNDO ;

		semop(semid, &myop, 1);

		(*p) ++ ;

		memset(&myop, 0, sizeof(myop));

		myop.sem_num = 0 ;
		myop.sem_op = 1 ;
		myop.sem_flg = SEM_UNDO ;

		semop(semid, &myop, 1);



	}
	printf("over!\n");

	while(1);



}
