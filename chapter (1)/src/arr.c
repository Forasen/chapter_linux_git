#include "arr.h"
void arr_init(int* arr, int len)
{
	int index ;
	for(index = 0; index < len ; index ++)
	{
		arr[index] = rand()%100;
	}
}



void arr_show(char* str, int* arr, int len)
{
	int index ;
	printf("%s: ", str);
	for(index = 0; index < len; index ++)
	{
		printf("%4d", arr[index]);
	}
	printf("\n");
}

