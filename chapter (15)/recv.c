#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
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
int main(int argc, char* argv[])//ip  port
{
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

	seraddr.sin_port = htons(atoi(argv[2]));

	seraddr.sin_addr.s_addr = inet_addr(argv[1]);

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

	int fd_client ;
	struct sockaddr_in peeraddr ;
	socklen_t sock_len = sizeof(peeraddr) ;

	fd_client = accept(fd_listen, (struct sockaddr*)&peeraddr, &sock_len);

	printf("%s:%d connect!\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port) );


	int* arr = (int*)calloc(1024*1024, 4);
	int len ;
	recv(fd_client, &len, 4, 0);
int recv_len =recvn(fd_client, (char*)arr, len);
	printf("readn: %d\n", recv_len);

	close(fd_client);
	close(fd_listen);








	return 0 ;
}
