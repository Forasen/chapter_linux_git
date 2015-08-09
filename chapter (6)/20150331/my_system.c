#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
	int sys_ret ;
	printf("my_system: %d\n", getpid());
	// sys_ret:0xAABB
	// 1. normal  AA = (cmd return) BB= 00
	// 2. abnormal AA=00, high_bit(BB) ? left a core_dump file: no left core_file . low-7bits refer to  signal number
	// kill -9 pid(my_add) ret = 0x0009
	// kill -3 pid(my_add) ret = 0x0083    BB:1000 0003
	sys_ret = system("./my_add 1 3");//0x0400
	printf("res: %04x\n", sys_ret);
	printf("----------------------------\n");
	return 0 ;
}
void test1()
{
	system("ps -aux");
}
