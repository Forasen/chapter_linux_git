#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc, char* argv[])//1_2.fifo  2_1.fifo
{
	int fd_send, fd_recv ;
	fd_send = open(argv[1], O_WRONLY);//1_2.fifo
	fd_recv = open(argv[2], O_RDONLY);
	if(fd_send == -1 || fd_recv == -1)
	{
		perror("open");
		exit(1);
	}

	printf("open success!: send:%d,recv: %d \n", fd_send, fd_recv);


	char msg[1024] ;
	while(memset(msg, 0, 1024), fgets(msg, 1024, stdin)!= NULL)
	{
		write(fd_send, msg, strlen(msg));
		memset(msg, 0, 1024);
		read(fd_recv, msg, 1023);

		printf("from2: %s\n",msg );
	}

	printf("bye!\n");
	write(fd_send, "bye\n", 4); //"bype"
	close(fd_recv);

	close(fd_send);
	return 0 ;
}
