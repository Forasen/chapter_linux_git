#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc, char* argv[])//1_2.fifo 2_1.fifo
{
	int fd_recv, fd_send ;
	int readn ;
	fd_recv = open(argv[1], O_RDONLY);
	fd_send = open(argv[2], O_WRONLY);
	if(fd_send == -1 || fd_recv == -1)
	{
		perror("open");
		exit(1);
	}
	printf("open success! send: %d, recv: %d\n", fd_send, fd_recv);

	char recv_msg[1024];

	while(memset(recv_msg, 0, 1024), (readn = read(fd_recv, recv_msg, 1023)) != 0)
	{
		printf("from 1:  %s\n", recv_msg);

		memset(recv_msg, 0, 1024);
		fgets(recv_msg, 1024, stdin);

		write(fd_send, recv_msg, strlen(recv_msg));
	}
	close(fd_recv);
	close(fd_send);
	return 0 ;
}
