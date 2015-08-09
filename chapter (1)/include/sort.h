#ifndef __SORT_H__
#define __SORT_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int tmp ;
#define swap(left, right) do{\
	tmp = left ;\
	left = right;\
	right =tmp;\
}while(0)
		

void buble_sort(int* arr, int len);
void insert_sort(int* arr, int len);
void select_sort(int* arr, int len);
void quick_sort(int* arr, int len);
void heap_sort(int* arr, int len);
#endif
