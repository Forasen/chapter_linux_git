#include "sort.h"
void select_sort(int* arr, int len)
{
	int min_index, index ;
	int pos ;
	for(pos = 0; pos < len; pos ++)
	{
		min_index = pos ;
		for(index = pos + 1; index < len; index ++)
		{
			if(arr[index] < arr[min_index])
			{
				min_index = index ;
			}
		}
		if(min_index != pos)
		{
			swap(arr[min_index], arr[pos]);
		}
	}
}

