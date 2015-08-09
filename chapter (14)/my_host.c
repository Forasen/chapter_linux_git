#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
int main(int argc, char* argv[])
{
	int host_num = 0x12345678;
	int num1 = htonl(host_num);
	int num2 = ntohl(host_num);

	int port = 0x1122;
	int port1 = htons(port);
	int port2 = ntohs(port);
	return 0 ;
}
