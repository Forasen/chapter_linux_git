#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define	FIFO_13 "./13.fifo"
#define FIFO_31 "./31.fifo"
#define FIFO_23 "./23.fifo"
#define FIFO_32 "./32.fifo"
int main(int argc, char* argv[])
{
	int fd_13, fd_31, fd_23, fd_32 ;

	fd_13 = open(FIFO_13, O_RDONLY);
	fd_31 = open(FIFO_31, O_WRONLY);

	fd_23 = open(FIFO_23, O_RDONLY);

	fd_32 = open(FIFO_32, O_WRONLY);

	printf("13: %d, 31: %d, 23: %d, 32: %d\n", fd_13, fd_31, fd_23, fd_32);

	char msg[1024] ;
	int readn ;
	int flag1, flag2 ;
	flag1 = 1 ;
	flag2 = 1 ;
	while(1)
	{
		// recv 1
		if(flag1)
		{
			memset(msg, 0, 1024);
			readn = read(fd_13, msg, 1023);
			if(readn == 0)
			{
				printf("1 off !\n");

				close(fd_13);
				close(fd_31);

				fd_31 = -1 ;
				flag1 = 0 ;

			}else 
			{
				printf("from 1: %d: %s\n",readn,  msg);
			}
		}

		//reacv 2
		if(flag2)
		{
			memset(msg, 0, 1024);
			readn = read(fd_23, msg, 1023);
			if(readn == 0)
			{
				printf("2 off !\n");

				close(fd_23);
				close(fd_32);

				fd_32 = -1 ;
				flag2 = 0 ;
			}else 
			{
				printf("from 2: %d: %s\n",readn,  msg);
			}
		}

		// send 1, 2
		memset(msg, 0, 1024);
		printf(">>:\n ");
		if(fgets(msg, 1024, stdin) == NULL)
		{
			printf("3 off");
			close(fd_13);
			close(fd_31);
			close(fd_23);
			close(fd_32);
			break ;

		}
		if(fd_31 != -1)
		{
			write(fd_31, msg, strlen(msg));
		}
		if(fd_32 != -1)
		{
			write(fd_32, msg, strlen(msg));
		}
		if(fd_31 == -1 && fd_32 == -1)
		{
			printf("1, 2 off!\n");
			break ;
		}




	}


	return 0 ;
}

