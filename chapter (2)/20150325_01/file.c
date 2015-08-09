#include<stdio.h>
#include<stdlib.h>
typedef struct tag_date
{
	int d_year;
	int d_mon ;
	int d_day ;
}date_t ;

typedef struct tag_acc
{
	int acc_id;
	char acc_name[32];
	date_t acc_birth;
}acc_t ;
int my_cmp(const void* left, const void* right);
int main(int argc, char* argv[])
{
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		printf("fopen!\n");
		exit(1);
	}
	acc_t arr[5];
	int index ;
	char line[128];
	for(index = 0; index < 5; index ++)
	{
		fgets(line, 128, fp);
		sscanf(line, "%d%s%d%d%d", &arr[index].acc_id, arr[index].acc_name, &arr[index].acc_birth.d_year, &arr[index].acc_birth.d_mon, &arr[index].acc_birth.d_day);
	}
	
	fclose(fp);
	qsort(arr,5,  sizeof(acc_t), my_cmp);

	for(index = 0; index < 5; index ++)
	{
		fprintf(stdout, "%-5d%10s%d-%d-%d\n", arr[index].acc_id, arr[index].acc_name, arr[index].acc_birth.d_year, arr[index].acc_birth.d_mon, arr[index].acc_birth.d_day );
	}

	return 0 ;
}
int my_cmp(const void* left, const void* right)
{
	acc_t* pleft = (acc_t*)left ;
	acc_t* pright = (acc_t*)right;
	if(pleft ->acc_birth.d_year < pright->acc_birth.d_year)
	{
		return -1 ;
	}else if(pleft->acc_birth.d_year == pright->acc_birth.d_year)
	{
		if(pleft->acc_birth.d_mon < pright->acc_birth.d_mon)
		{
			return -1 ;
		}else if(pleft->acc_birth.d_mon == pright->acc_birth.d_mon)
		{
			if(pleft ->acc_birth.d_day < pright->acc_birth.d_day)
			{
				return -1 ;
			}else if(pleft ->acc_birth.d_day == pright ->acc_birth.d_day)
			{
				return 0 ;
			}else
			{
				return 1 ;
			}
		}else 
		{
			return 1 ;
		}
	}else 
	{
		return 1 ;
	}
}
