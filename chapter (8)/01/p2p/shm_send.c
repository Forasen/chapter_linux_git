#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
typedef struct my_mem
{
	int m_lock ;
	int m_unshow ;
	char m_buf[128] ;
}mem_t, *pmem_t ;

void Lock(pmem_t pm)
{
	while(pm ->m_lock == 0)
	{
		sleep(1);
	}
	//get lock 
	pm -> m_lock = 0 ;
}

void unLock(pmem_t pm)
{
	pm -> m_lock = 1 ;
}
int main(int argc, char* argv[])
{
	int shmid ;
	char line[128];
	shmid = shmget((key_t)1234, sizeof(mem_t), IPC_CREAT|0666);
	if(shmid == -1)
	{
		perror("shmget");
		exit(1);
	}
	pmem_t pm = (pmem_t)shmat(shmid, NULL, 0);

	if((void*)pm == (void*)-1)
	{
		perror("shmat");
		exit(1);
	}
	pm ->m_lock = 1 ;

	pm ->m_unshow = 0 ;

//	memset( pstr, 0, 128);

	printf("pid: %d\n", getpid());
	while(memset(line, 0, 128), read(0, line, 127) != 0)
	{
		Lock(pm);
		while( pm -> m_unshow == 1)
		{
			unLock(pm);
			sleep(1);

			Lock(pm);
		}

		strcpy(pm ->m_buf, line);

		pm ->m_unshow = 1 ;

		unLock(pm);
		
	}


	sleep(30);
	shmdt(pm);

	shmctl(shmid, IPC_RMID, NULL);


	return 0 ;
}
