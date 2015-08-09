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
#define MSG_ON 1
#define MSG_OFF 2
#define MSG_NOR 3
#define SIZE 1024
typedef struct msg
{
	int msg_type ;
	char msg_buf[SIZE];
}msg_t, *pmsg_t ;
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
int main(int argc, char* argv[])// host_ip host_prot  server_ip  server_port
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
			printf("msg: %s\n", buf);
		}
		exit(1);
	}

	
		printf("parent: %d\n", getpid());
	signal(3, usr2_handle);
	struct sockaddr_in peeraddr ;
	peeraddr.sin_family = AF_INET ;
	peeraddr.sin_port = htons(atoi(argv[4]));
	peeraddr.sin_addr.s_addr = inet_addr(argv[3]);
//send on msg
	msg_t  clientmsg ;
	memset(&clientmsg, 0, sizeof(msg_t));
	clientmsg.msg_type = MSG_ON;
	
	sprintf(clientmsg.msg_buf, "%s:%s on!\n", argv[1], argv[2] );

	sendto(sfd, &clientmsg, sizeof(msg_t), 0,(struct sockaddr*)&peeraddr, sizeof(peeraddr) );
	

	while(memset(&clientmsg, 0, sizeof(msg_t)), fgets( clientmsg.msg_buf, 1024, stdin) != NULL)
	{
		clientmsg.msg_type = MSG_NOR ;
		sendto(sfd, &clientmsg, sizeof(msg_t), 0,(struct sockaddr*)&peeraddr, sizeof(peeraddr) );
	}

	//send msg off
	memset(&clientmsg, 0, sizeof(msg_t));
	clientmsg.msg_type = MSG_OFF;
	
	sprintf(clientmsg.msg_buf, "%s:%s off!\n", argv[1], argv[2] );

	sendto(sfd, &clientmsg, sizeof(msg_t), 0,(struct sockaddr*)&peeraddr, sizeof(peeraddr) );
	//msg off
	
	kill( pid, 2 );
	wait(NULL);



	close(sfd);
	




	return 0 ;
}
