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

//	fd_23 = open(FIFO_23, O_RDONLY);

//	fd_32 = open(FIFO_32, O_WRONLY);

	printf("13: %d, 31: %d\n", fd_13, fd_31);

	char msg[1024] ;
	int readn ;
	int flag1, flag2 ;
	flag1 = 1 ;
	flag2 = 1 ;
	while(1)
	{
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
		// recv 1






	}


	return 0 ;
}

