#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<unistd.h>
void scan_dir(char* path, int width);
int main(int argc, char* argv[])// dir
{
	scan_dir(argv[1], 1);
	return 0 ;
}
void scan_dir(char* path, int width)
{
	DIR* pdir ;
	struct dirent* pent ;
	
	struct stat entstat ;
	char fullpath[256] ;
	pdir = opendir(path);
	
	if(pdir == NULL)
	{
		perror("opendir");
		exit(1);
	}

	while((pent = readdir(pdir)) != NULL)
	{
		if(strcmp(pent ->d_name, ".") ==0 || strcmp(pent ->d_name, "..") == 0)
		{
			continue ;
		}
		memset(fullpath, 0, 256);
		
		sprintf(fullpath, "%s/%s", path, pent ->d_name);
		
		memset(&entstat, 0, sizeof(entstat));

		if(-1 == lstat(fullpath, &entstat))
		{
			perror("lstat");
			exit(1);
		}

		if(S_ISDIR(entstat.st_mode))
		{
			printf("%*s%s\n", width, " ", pent->d_name);//
			scan_dir(fullpath, width + 5);

			
		}else 
		{
			printf("%*s%s\n", width, " ", pent->d_name);//
		}




	}


}

int myadd(int left, int right)
{
	return printf("%*s%*s", left, " ", right, " ");
}
