#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define	FIFO_12 "./12.fifo"
#define FIFO_13 "./13.fifo"
#define FIFO_21 "./21.fifo"
#define FIFO_31 "./31.fifo"
int main(int argc, char* argv[])
{
	int fd_12, fd_21, fd_13, fd_31 ;

	fd_12 = open(FIFO_12, O_WRONLY);
	fd_21 = open(FIFO_21, O_RDONLY);

	fd_13 = open(FIFO_13, O_WRONLY);

	fd_31 = open(FIFO_31, O_RDONLY);

	char msg[1024];
	int readn ;
	int flag2, flag3 ;
	flag2 = 1 ;
	flag3 = 1 ;
	printf("12: %d, 21: %d, 13: %d, 31: %d\n", fd_12, fd_21, fd_13, fd_31);
	while(1)
	{
		// send 2, 3
		printf(">>:\n ");
		memset(msg, 0, 1024);
		if(fgets(msg, 1024, stdin) == NULL)
		{
			close(fd_12);
			close(fd_21);
			close(fd_13);
			close(fd_31);
			printf("1 off !\n");
			break ;
		}
		if(fd_12 != -1)
		{
			write(fd_12, msg, strlen(msg));
		}
		if(fd_13 != -1)
		{
			write(fd_13, msg, strlen(msg));
		}
		if(fd_12 == -1 && fd_13 == -1)
		{
			printf("2, 3 off!\n");
			break ;
		}

		// recv 2
		if(flag2)
		{
			memset(msg, 0, 1024);
			readn = read(fd_21, msg, 1023);
			if(readn == 0)
			{
				printf("2 off!\n");
				close(fd_12);
				close(fd_21);
				fd_12 = -1 ;
				flag2 = 0 ;
			}else 
			{
				printf("from 2: %d: %s\n",readn,  msg);
			}
		}

		//reacv 3
		if(flag3)
		{
			memset(msg, 0, 1024);
			readn = read(fd_31, msg, 1023);
			if(readn == 0)
			{
				printf("3 off!\n");
				close(fd_13);
				close(fd_31);
				fd_13 = -1 ;
				flag3 = 0;
			}else 
			{
				printf("from 3: %d: %s\n",readn,  msg);
			}
		}


	}


	return 0 ;
}
