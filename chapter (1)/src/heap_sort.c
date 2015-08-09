#include "sort.h"
void adjust_down(int* arr, int pos, int end)
{
	int max_child = (pos << 1) + 1 ;
	int key = arr[pos] ;
	while(max_child <= end)
	{
		if(max_child + 1 <= end)
		{
			if(arr[max_child + 1] > arr[max_child] )
			{
				max_child = max_child + 1 ;
			}
		}
		if(key < arr[max_child])
		{
			arr[pos] = arr[max_child] ;
			pos = max_child ;
			max_child = (pos << 1) + 1 ;
		}else 
		{
			break ;
		}
	}
		arr[pos] = key ;
}
void heap_sort(int* arr, int len)
{
	int index ;
	for(index = (len - 2) >> 1 ; index >= 0; index --)
	{
		adjust_down(arr, index, len - 1);
	}
	for(index = len - 1; index >= 1; index --)
	{
		swap(arr[index], arr[0]);
		adjust_down(arr, 0, index - 1);
	}
}
