#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(int argc, char* argv[])
{
	char* str = "192.168.1.1" ;
	char* str6 ="00:00:00:00:00:C2:00:02";
	struct in_addr myip ;
	if(0 == inet_aton(str, &myip))
	{
		printf("inet_aton failed!\n");
		exit(1);
	}
	char* ip = inet_ntoa(myip);

	struct in_addr addr ;
	addr.s_addr = inet_addr(str);

	struct in_addr addr2 ;

	if(1 != inet_pton(AF_INET, str, &addr2))
	{
		printf("pton fail!\n");
		exit(1);
	}

	struct in6_addr addr3 ;

	inet_pton(AF_INET6, str6, &addr3);

	return 0 ;
}
