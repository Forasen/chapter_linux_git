#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main(int argc, char* argv[])
{
	int shmid ;
	shmid = shmget((key_t)1234, 128, 0);
	if(shmid == -1)
	{
		perror("shmget");
		exit(1);
	}
	char* pstr = (char*)shmat(shmid, NULL, 0);

	printf("pid: %d, shm: %s\n", getpid(), pstr);
	
	shmdt(pstr);



	return 0 ;
}
