#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define	FIFO_12 "./12.fifo"
#define FIFO_21 "./21.fifo"
#define FIFO_23 "./23.fifo"
#define FIFO_32 "./32.fifo"
int main(int argc, char* argv[])
{
	int fd_12, fd_21, fd_23, fd_32 ;

	fd_12 = open(FIFO_12, O_RDONLY);
	fd_21 = open(FIFO_21, O_WRONLY);

	fd_23 = open(FIFO_23, O_WRONLY);

	fd_32 = open(FIFO_32, O_RDONLY);

	printf("12: %d, 21: %d, 23: %d, 32: %d\n", fd_12, fd_21, fd_23, fd_32);
	char msg[1024] ;
	int readn ;
	int flag1, flag3 ;
	flag1 = 1 ;
	flag3 = 1 ;
	while(1)
	{
		// recv 1
		if(flag1)
		{
			memset(msg, 0, 1024);
			readn = read(fd_12, msg, 1023);
			if(readn == 0)
			{
				printf("1 off!\n");
				close(fd_12);
				close(fd_21);

				fd_21 = -1 ;
				flag1 = 0 ;
			}else 
			{
				printf("from 1: %d: %s\n",readn,  msg);
			}
		}

		// send 1, 3
		memset(msg, 0, 1024);
		printf(">>:\n ");
		if(fgets(msg, 1024, stdin) == NULL)
		{
			printf("2 off!\n");
			close(fd_12);
			close(fd_21);
			close(fd_23);
			close(fd_32);
			break ;
		}
		if(fd_21 != -1)
		{
			write(fd_21, msg, strlen(msg));
		}
		if(fd_23 != -1)
		{
			write(fd_23, msg, strlen(msg));
		}
		if(fd_21 == -1 && fd_23 == -1)
		{
			printf("1, 3 off!\n");
			break ;
		}


		//reacv 3
		if(flag3)
		{
			memset(msg, 0, 1024);
			readn = read(fd_32, msg, 1023);
			if(readn == 0)
			{
				printf("3 off !\n");
				close(fd_23);
				close(fd_32);

				fd_23 = -1 ;
				flag3 = 0;
			}else 
			{
				printf("from 3: %d: %s\n",readn,  msg);
			}
		}


	}


	return 0 ;
}
