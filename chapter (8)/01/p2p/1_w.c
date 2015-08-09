#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/time.h>
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
	int fd_s, fd_r ;

	//open fifo  12.fifp 21.fifo
	fd_s = open("./12.fifo", O_WRONLY);

	fd_r = open("./21.fifo", O_RDONLY);

	printf("fd_s: %d, fd_r: %d\n", fd_s, fd_r);

	//shm
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


	//select
	fd_set rds ;
	struct timeval tm ;
	int ret ;
	while(1)
	{
		FD_ZERO(&rds);

		FD_SET(0, &rds);

		FD_SET(fd_r, &rds);

		tm.tv_usec = 0 ;
		tm.tv_sec = 5;

		ret = select(1024, &rds, NULL, NULL, &tm);

		if(ret == 0)
		{
			continue ;
		}else if(ret > 0)
		{
			if(FD_ISSET(0, &rds))
			{
				memset(line, 0, 128);
				read(0, line, 127);
				write(fd_s, line, strlen(line));
			}
			if(FD_ISSET(fd_r, &rds ))
			{
				memset(line, 0, 128);
				read(fd_r, line, 127);

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
		}





	}


	close(fd_s);
	close(fd_r);
	shmdt(pm);

	shmctl(shmid, IPC_RMID, NULL);


	return 0 ;
}
