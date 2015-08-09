#include "arr.h"
#include "sort.h"
int main(int argc, char* argv[])
{

	int arr[15] ;
	arr_init(arr, 15);
	arr_show("before", arr, 15);
	buble_sort(arr, 15);
	arr_show("buble", arr, 15);

	arr_init(arr, 15);
	arr_show("before", arr, 15);
	select_sort(arr, 15);
	arr_show("select", arr, 15);

	arr_init(arr, 15);
	arr_show("before", arr, 15);
	insert_sort(arr, 15);
	arr_show("insert", arr, 15);

	arr_init(arr, 15);
	arr_show("before", arr, 15);
	quick_sort(arr, 15);
	arr_show("quick", arr, 15);

	arr_init(arr, 15);
	arr_show("before", arr, 15);
	heap_sort(arr, 15);
	arr_show("heap", arr, 15);
	return 0 ;
}

