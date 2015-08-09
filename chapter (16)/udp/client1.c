#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<signal.h>
void usr2_handle(int num)
{
	printf("us2\n");
	wait(NULL);
	exit(1);
}
void usr1_handle(int num)
{
	printf("usr1\n");
	exit(1);
}
int main(int argc, char* argv[])// host_ip host_prot  peer_ip peer_port
{
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr ;
	addr.sin_family = AF_INET ;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	if(-1 == bind(sfd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		perror("bind");
		exit(1);
	}
	pid_t pid ;
	if( (pid = fork()) == 0)//recv
	{
		printf("child: %d\n", getpid());
		signal(2, usr1_handle);
		while(1)	
		{
			char buf[1024]="";
			struct sockaddr_in peeraddr ;
			socklen_t len = sizeof(peeraddr);
			recvfrom(sfd, buf, 1023, 0, (struct sockaddr*)&peeraddr, &len);
			if(strcmp(buf , "1001") == 0)
			{
				printf("over!\n");
				break ;
			}
			printf("%s:%d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
			printf("msg: %s\n", buf);
		}
		kill( getppid(), 3);
		exit(1);
	}

	
		printf("parent: %d\n", getpid());
	signal(3, usr2_handle);
	struct sockaddr_in peeraddr ;
	peeraddr.sin_family = AF_INET ;
	peeraddr.sin_port = htons(atoi(argv[4]));
	peeraddr.sin_addr.s_addr = inet_addr(argv[3]);
	char msg[1024] ;
	int ret  ;
	while(memset(msg, 0, 1024), fgets( msg, 1024, stdin) != NULL)
	{
		ret = sendto(sfd, msg, strlen(msg), 0,(struct sockaddr*)&peeraddr, sizeof(peeraddr) );
		printf("send to: %d\n", ret);
	}

	char* pend = "1001" ;
	sendto(sfd, pend, strlen(pend), 0, (struct sockaddr*)&peeraddr, sizeof(peeraddr));
	kill( pid, 2 );
	wait(NULL);



	close(sfd);





	return 0 ;
}
