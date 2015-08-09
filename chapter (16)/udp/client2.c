#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define PORT 8888
#define IP "120.24.236.135"
int main(int argc, char* argv[])
{
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in peeraddr, myaddr ;
	peeraddr.sin_family = AF_INET ;
	peeraddr.sin_port = htons(PORT);
	peeraddr.sin_addr.s_addr = inet_addr(IP);

	myaddr.sin_family = AF_INET ;
	myaddr.sin_port = htons(9999);
	myaddr.sin_addr.s_addr = inet_addr(IP);

	
	if(-1 == bind(sfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))
	{
		perror("bind");
		exit(1);
	}

	char* p = "hello world\n" ;
	sendto(sfd, p, strlen(p), 0,(struct sockaddr*)&peeraddr, sizeof(peeraddr) );

	char buf[1024]="";
	struct sockaddr_in addr ;
	socklen_t len = sizeof(addr);
//	recvfrom(sfd, buf, 1023, 0, (struct sockaddr*)&addr, &len);
	//printf("%s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	recvfrom(sfd, buf, 1023, 0,  NULL, NULL);
	printf("msg: %s\n", buf);


	close(sfd);





	return 0 ;
}
