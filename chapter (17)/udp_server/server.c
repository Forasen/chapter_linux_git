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

typedef struct node
{
	struct sockaddr_in nd_client ;
	struct node* nd_next ;
}node_t, *pnode_t;

typedef void (*pfun_t)(int, struct sockaddr_in*,  char*);

typedef void (*phandle_t)(int, pnode_t*, char*,  struct sockaddr_in*, pfun_t);

void link_insert(pnode_t* pphead, struct sockaddr_in* peeraddr);

void link_delete(pnode_t* pphead, struct sockaddr_in* peeraddr);

void msg_send(int sfd, struct sockaddr_in* peeraddr, char* msg);

void link_visit(pnode_t* pphead, pfun_t, int sfd, char* msg);

void msg_on_handle(int sfd, pnode_t* pphead, char* msg,  struct sockaddr_in* fromaddr, pfun_t send_fun);
void msg_off_handle(int sfd, pnode_t* pphead, char* msg, struct sockaddr_in* fromaddr, pfun_t send_fun);
void msg_normal_handle(int sfd, pnode_t* pphead, char* msg, struct sockaddr_in* fromaddr, pfun_t sendfun);
//msg_on: peeraddr insert link , tell them  on
//msg_nor: tell them what you say
//msg_off: peeraddr delete link , tell them  off
int main(int argc, char* argv[])//ip port
{
	phandle_t handle_arr[4] = {NULL, &msg_on_handle, &msg_off_handle, &msg_normal_handle};
	pnode_t plist = NULL ;
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sfd == -1)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in  seraddr;

	seraddr.sin_family  = AF_INET ;

	seraddr.sin_port = htons(atoi(argv[2]));

	seraddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(-1 == bind(sfd, (struct sockaddr*)&seraddr, sizeof(seraddr)))
	{
		perror("bind");
		close(sfd);
		exit(1);
	}
	struct sockaddr_in clientaddr ;
	socklen_t len = sizeof(clientaddr) ;
	msg_t clientmsg ;
	while(1)
	{
		memset(&clientaddr, 0, sizeof(clientaddr));
		memset(&clientmsg, 0, sizeof(clientmsg));
		recvfrom(sfd, &clientmsg, sizeof(msg_t), 0,  (struct sockaddr*)&clientaddr, &len );
//typedef void (*phandle_t)(int, pnode_t*, char*,  struct sockaddr_in*, pfun_t);
		(*handle_arr[clientmsg.msg_type])(sfd, &plist, clientmsg.msg_buf, &clientaddr, &msg_send);


	}

	return 0 ;
}
//insert at head
void link_insert(pnode_t* pphead, struct sockaddr_in* peeraddr)
{
	pnode_t pnew = (pnode_t)calloc(1, sizeof(node_t)) ;

	pnew ->nd_client = *peeraddr ;

	pnew ->nd_next = *pphead ;

	*pphead = pnew ;
}
//
void link_delete(pnode_t* pphead, struct sockaddr_in* peeraddr)
{

	pnode_t pcur, ppre; 
	pcur = *pphead ;
	ppre = NULL ;
	while(pcur)
	{
		if(pcur ->nd_client.sin_port == peeraddr ->sin_port && pcur ->nd_client.sin_addr.s_addr == peeraddr ->sin_addr.s_addr)
		{
			break ;
		}
		ppre = pcur ;
		pcur = pcur ->nd_next ;
	}
	if(pcur)
	{
		if(ppre == NULL)
		{
			*pphead = pcur ->nd_next ;
			free(pcur);
		}else
		{
			ppre ->nd_next = pcur ->nd_next ;
			free(pcur) ;
		}
	}

}

void msg_send(int sfd, struct sockaddr_in* peeraddr, char* msg)
{
	sendto(sfd, msg, strlen(msg), 0, (struct sockaddr*)peeraddr, sizeof(*peeraddr) );
}

void link_visit(pnode_t* pphead, pfun_t send_func, int sfd, char* msg)
{
	pnode_t pcur = *pphead ;
	while(pcur)
	{
		(*send_func)(sfd, &pcur ->nd_client, msg);
		pcur = pcur -> nd_next ;
	}
}

void msg_on_handle(int sfd, pnode_t* pphead, char* msg,  struct sockaddr_in* fromaddr, pfun_t send_func)
{
	link_insert(pphead, fromaddr );

	link_visit(pphead, send_func, sfd, msg );

}
void msg_off_handle(int sfd, pnode_t* pphead, char* msg, struct sockaddr_in* fromaddr, pfun_t send_func)
{
	link_delete(pphead, fromaddr);

	link_visit(pphead, send_func, sfd, msg );

}
void msg_normal_handle(int sfd, pnode_t* pphead, char* msg, struct sockaddr_in* fromaddr, pfun_t send_func)
{

	link_visit(pphead, send_func, sfd, msg );
}
