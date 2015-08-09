#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main(int argc, char* argv[])
{
	int shmid ;
	shmid = shmget((key_t)1234, 128, IPC_CREAT);
	if(shmid == -1)
	{
		perror("shmget");
		exit(1);
	}
	char* pstr = (char*)shmat(shmid, NULL, 0);

	if((void*)pstr == (void*)-1)
	{
		perror("shmat");
		exit(1);
	}

//	memset( pstr, 0, 128);

	printf("pid: %d\n", getpid());
	strcpy(pstr, "hello world!\n");

	sleep(30);
	shmdt(pstr);

	shmctl(shmid, IPC_RMID, NULL);


	return 0 ;
}
