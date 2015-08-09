#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static int g_val1 ;//BSS 数据段
int g_val2 = 3 ;//数据段
int func(int a, int b);//堆栈
int g_val3 = 1024;//数据段
int main(int argc, char* argv[])
{
	{
		int l_val1 ;//堆栈
		int l_val2 = 33 ;//堆栈
	}
	func(3, 6);

	//p 堆栈  p的值对应的内存在堆空间
	int* p = (int*)calloc(5, sizeof(int));
	// 堆栈  "hello wold"数据段（只读区）
	char* pstr = "hello world";
	return 0 ;
}
