#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{

	FILE* fp = fopen(argv[1], "r");
	int val ;
	if(fp == NULL)
	{
		printf("fopen!\n");
		exit(1);
	}
	int index ;
	/*
	for(index = 1; index <= 100; index ++)
	{
		fwrite(&index, sizeof(index), 1, fp);
	}
	fclose(fp);
	*/
	while(printf("enter:"), scanf("%d", &index) != EOF)
	{
		fseek(fp, (index - 1) << 2, SEEK_SET );
		fread(&val, sizeof(1), 1, fp);
		printf("index: %d -> %d\n", index, val);
		
	}
	fclose(fp);
	return 0 ;
}
