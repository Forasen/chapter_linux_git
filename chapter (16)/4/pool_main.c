#include"pool_thread.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<dirent.h>
#include<signal.h>
#include<sys/wait.h>
#include<pthread.h>
#define DOWN_PATH "/home/comst/download"

void handle_request(int sfd);
void show(int sfd) ;
int recvn(int sfd, char* buf, int len);
int sendn(int sfd, char* buf, int len);
void* handle(void* arg)
{
	
	//pool_get
	//excute_task
	pthreadspool_t ppool = (pthreadspool_t)arg ;
	elem_t fd_client ;
	while(1)
	{
		pool_get(ppool, &fd_client);
		handle_request(fd_client);
		close(fd_client);

	}
}
int main(int argc, char* argv[])//capacity  num ip  port
{
	if(argc != 5)
	{
		printf("EXE QUE_CAPACITY THREADS_NUM IP PORT!\n");
		exit(1);
	}
	//fd_listen
	int fd_listen ;
	fd_listen = socket(AF_INET, SOCK_STREAM, 0);
	if(fd_listen == -1)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in seraddr ;

	memset(&seraddr, 0, sizeof(seraddr));

	seraddr.sin_family = AF_INET ;

	seraddr.sin_port = htons(atoi(argv[4]));

	seraddr.sin_addr.s_addr = inet_addr(argv[3]);

	if(-1 == bind(fd_listen, (struct sockaddr*)&seraddr, sizeof(seraddr)) )
	{
		perror("bind");
		close(fd_listen);
		exit(1);
	}

	if(-1 == listen(fd_listen, 10))
	{
		perror("listen");
		close(fd_listen);
		exit(1);
	}
	//
	//thread_pool
	threadspool_t mypool ;

	pool_init(&mypool, atoi(argv[1]), atoi(argv[2]), handle );

	pool_on(&mypool);

	char buf[128] ;

	int fd_client ;
	struct sockaddr_in peeraddr ;
	socklen_t sock_len = sizeof(peeraddr) ;
	
	while(1)
	{
		fd_set rds ;
		FD_ZERO(&rds);

		FD_SET(fd_listen, &rds);

		struct timeval tm ;
		tm.tv_sec = 1 ;
		tm.tv_usec = 0 ;

		if(0 == select(1024, &rds, NULL, NULL, &tm))
		{
			continue ;
		}
		if(FD_ISSET(fd_listen, &rds))
		{
			
			fd_client = accept(fd_listen, (struct sockaddr*)&peeraddr, &sock_len);
			printf("%s:%d connect!\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
			//init a task ;
			elem_t val = fd_client ; ;
			pool_put(&mypool, val);
		}



	}

	pool_off(&mypool);

	pool_destroy(&mypool);


	return 0 ;
}
int recvn(int sfd, char* buf, int len)
{
	int recv_sum = 0 ;
	int recv_ret ;

	while(recv_sum < len)
	{
		recv_ret = recv(sfd, (char*)buf + recv_sum , len - recv_sum, 0);
		

		recv_sum += recv_ret ;
	}
	return recv_sum ;
}
int sendn(int sfd, char*buf, int len)
{
	int send_sum = 0 ;
	int send_ret ;

	while(send_sum < len)
	{
		send_ret = send(sfd, (char*)buf + send_sum, len - send_sum, 0);

		
		send_sum += send_ret ;

	}
	return send_sum;
}
void handle_request(int sfd)
{
	show(sfd);
	char target_file[128] = "" ;
	char full_path[256] = "" ;
	int len ;
	recv(sfd, &len, 4, 0);
	recvn(sfd, target_file, len);
	printf("down file: %s\n", target_file);
	sprintf(full_path, "%s/%s", DOWN_PATH, target_file);
	
	FILE* fp = fopen(full_path, "r");
	if(fp == NULL)
	{
		perror("fopen");
		len = -1 ;
		send(sfd, &len, 4, 0);
		close(sfd);
		return ;
	}
	len = 1 ;
	send(sfd, &len, 4, 0);
	char msg[1024] ;
	while(memset(msg, 0, 1024), fgets(msg, 1024, fp) != NULL)
	{
		len = strlen(msg);
		send(sfd, &len, 4, 0);

		sendn(sfd, msg, len);
	}
	len = 0 ;
	send(sfd, &len, 4, 0);

	close(sfd);

}
void show(int sfd) 
{

	DIR* pdir ; 
	pdir = opendir(DOWN_PATH);
	if(pdir == NULL)
	{
		perror("opendir");
		return ;
	}

	struct dirent* pent ;
	char buf[1024] = "" ;
	int len  ;
	while((pent = readdir(pdir)) != NULL)
	{
		if(strcmp(".", pent ->d_name) == 0 || strcmp("..", pent ->d_name) == 0)
		{
			continue ;
		}
		strcat(buf, "\n");
		strcat(buf, pent ->d_name);

	}

	len = strlen(buf);

	send(sfd, &len, 4, 0);
	sendn(sfd, buf, len);

	
}
