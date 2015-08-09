#include "sort.h"
static int partion(int* arr, int len)
{
	int index_i, index_j ;
	int key = arr[0] ;
	for(index_i = 0, index_j = 1; index_j < len; index_j ++)
	{
		if(arr[index_j] < key)
		{
			swap(arr[index_i + 1], arr[index_j]) ;
			index_i ++ ;
		}
	}
	swap(arr[index_i], arr[0]);
	return index_i ;
}
void quick_sort(int* arr, int len)
{
	if(len < 2)
	{
		//insert_sort(arr, len);
		return ;
	}else 
	{
		int k ;
		k = partion(arr, len);
		quick_sort(arr, k);
		quick_sort(arr + k + 1, len - k - 1);
	}
}

