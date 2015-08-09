#ifndef __COMMON__
#define __COMMON__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/time.h>
struct task
{
	int left; 
	int right ;
};
typedef struct task elem_t ; 
#endif
