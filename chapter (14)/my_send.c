#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(int argc, char* argv[])
{
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
	{
		perror("socket");
		exit(1);
	}
	
	struct sockaddr_in peeraddr ;

	peeraddr.sin_family = AF_INET ;

	peeraddr.sin_port = htons(1234);

	peeraddr.sin_addr.s_addr = inet_addr("120.24.236.135");

	if(-1 == connect(sfd, (struct sockaddr*)&peeraddr, sizeof(peeraddr)))
	{
		perror("connect");
		close(sfd);
	}

	char* p = "hello world" ;
	write(sfd, p, strlen(p));

	char buf[1024] = "" ;
	int readn = read(sfd, buf, 1023);

	printf("readn: %d: %s\n", readn, buf);

	close(sfd);
	return 0 ;
}
