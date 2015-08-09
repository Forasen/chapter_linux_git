#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/time.h>
#include<unistd.h>
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
		fd_set read_sets ;
		FD_ZERO(&read_sets);

		FD_SET(0, &read_sets);

		flag2 && FD_SET(fd_21, &read_sets);
		flag3 && FD_SET(fd_31, &read_sets);

		struct timeval  tm ;

		tm.tv_sec = 5 ;
		tm.tv_usec = 0 ;

		int nret = select(1024, &read_sets, NULL, NULL, &tm);
		printf("nret: %d\n", nret);
		if(FD_ISSET(0, &read_sets))// stdin ready
		{
			memset(msg, 0, 1024);
			read(0, msg, 1023);
			//		write(fd_12, msg, strlen(msg));
			//		write(fd_13, msg, strlen(msg));
			printf("read from stdin!\n");
		}
		if(FD_ISSET(fd_21, &read_sets))// client 2 send a message
		{
			printf("2 send a message!\n");
			memset(msg, 0, 1024);
			readn = read(fd_21, msg, 1023);
			if(readn == 0)
			{
				printf("2 off!\n");
				flag2 = 0 ;
				close(fd_21);
			}else 
			{
				printf("from 2: %s\n", msg);
			}

		}
		if(FD_ISSET(fd_31, &read_sets))// client3 send a messgae
		{
			printf("3 send a message!\n");
			memset(msg, 0, 1024);
			readn =read(fd_31, msg, 1023);
			if(readn == 0)
			{
				printf("3 off !\n");
				flag3 = 0 ;
				close(fd_31);
			}else
			{
				printf("from 3: %s\n", msg);
			}

		}


	}

	return 0 ;
}
