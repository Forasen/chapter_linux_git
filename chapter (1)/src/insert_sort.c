#include "sort.h"
void insert_sort(int* arr, int len)
{
	int pos, index ;
	int key ;
	for(index = 1; index < len; index ++)
	{
		key = arr[index] ;
		for(pos = index - 1; pos >= 0; pos --)
		{
			if(key < arr[pos])
			{
				arr[pos + 1] = arr[pos] ;
			}else 
			{
				break ;
			}
		}
		arr[pos + 1] = key ;
	}
}
