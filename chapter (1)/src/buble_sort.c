#include "sort.h"
void buble_sort(int* arr, int len)
{
	int up, down;
	int index ;
	up = -1;
	down = len ;
	while(up < down)
	{
		for(index = up + 1; index + 1 < down; index ++)	
		{
			if(arr[index] > arr[index + 1 ])
			{
				swap(arr[index], arr[index + 1]);				
			}	
		}
		down -- ;
		if(down <= up)
		{
			break ;
		}
		for(index = down - 1; index - 1 > up; index --)
		{
			if(arr[index] < arr[index - 1])
			{
				swap(arr[index], arr[index - 1]);
			}
		}
		up ++ ;
	}
}

