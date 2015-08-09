#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

//struct hostent {
//	char  *h_name;            /* official name of host */
//	char **h_aliases;         /* alias list */
//	int    h_addrtype;        /* host address type */
//	int    h_length;          /* length of address */
//	char **h_addr_list;       /* list of addresses */
//}

int main(int argc, char* argv[])
{
	char* host = "www.baidu.com" ;
	struct in_addr myaddr ;
	myaddr.s_addr = inet_addr("127.0.0.1");
	struct hostent* pent ;
	/*
	if(NULL == (pent =  gethostbyname(host)) )
	{
		perror("gethostbyname");
		exit(1);
	}*/
	if(NULL == (pent =  gethostbyaddr( (const void*)&myaddr, sizeof(myaddr), AF_INET)) )
	{
		herror("gethostbyaddr");
		exit(1);
	}
	printf("h_name: %s\n", pent ->h_name);
	int index ;
	for(index = 0; pent ->h_aliases[index] != NULL; index ++)
	{
		printf("alias[%d]:%s\n", index, pent ->h_aliases[index]);
	}
	printf("addrtype: %d, addrlen: %d\n", pent ->h_addrtype, pent ->h_length);
	for(index = 0; pent ->h_addr_list[index] != NULL; index ++)
	{
		printf("%d: %s\n", index, inet_ntoa(*(struct in_addr*)pent ->h_addr_list[index]));
	}

	return 0 ;

}
