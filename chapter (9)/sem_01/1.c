#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
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
	int semid = semget((key_t)1234, 1, IPC_CREAT | 0666);
	if(semid == -1)
	{
		perror("semget");
		exit(1);
	}

	union semun mysem ;
	memset(&mysem, 0, sizeof(mysem));
	mysem.val = 1 ;

	semctl(semid, 0, SETVAL, mysem);
	
	int semval = semctl(semid, 0, GETVAL);
	printf("semval: %d\n", semval);


	//shm
	int shmid = shmget((key_t)1024, 4, IPC_CREAT | 0666);
	if(shmid == -1)
	{
		perror("shm");
		exit(1);
	}
	int* p =(int*)shmat(shmid, NULL, 0);
	if((void*)p == (void*)-1)
	{
		perror("shmat");
		exit(1);
	}
	*p = 0 ;



	int cnt = atoi(argv[1]); ;




	while(cnt > 0)
	{
		cnt -- ;
		

		memset(&myop, 0, sizeof(myop));
		myop.sem_num = 0 ;
		myop.sem_op = -1;// semval = 0
		myop.sem_flg = SEM_UNDO ;

		semop(semid, &myop, 1);//P();


		(*p) ++ ;

		
		memset(&myop, 0, sizeof(myop));
		myop.sem_num = 0 ;
		myop.sem_op = 1;// semval = 0
		myop.sem_flg = SEM_UNDO ;

		semop(semid, &myop, 1);//V();
		

	}

	while(getchar() != EOF) ;
	printf("%d\n", *p);
	while(1);




}
