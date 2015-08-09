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
void time_handle(char*) ;
void mode2str(mode_t md, char* res);
int main(int argc, char* argv[])// dir
{
	DIR* pdir;
	char* ptm ;
	char perm[11] ;
	char path[256];
	struct stat my_stat ;
	struct dirent* pent;
	pdir = opendir(argv[1]);
	if(pdir == NULL)
	{
		perror("opendir");
		exit(1);
	}
	while( (pent = readdir(pdir) ) != NULL )
	{
		//	printf("inode: %d\n", pent ->d_ino);
		//	printf("offset: %u\n", pent ->d_off);
		//	printf("reclen: %d\n", pent ->d_reclen);
		//	printf("type: %d\n", pent ->d_type);
		memset(path, 0, 256);
		sprintf(path, "%s/%s", argv[1], pent -> d_name);

		memset(&my_stat, 0, sizeof(my_stat));

		if(lstat(path, &my_stat) == -1 )
		{
			perror("stat");
			exit(1);
		}
		ptm = ctime(&my_stat.st_mtime);
		time_handle(ptm);
		
		mode2str(my_stat.st_mode, perm);
		printf("%10s %d %5s %5s %5d %15s %10s\n", perm, my_stat.st_nlink, getpwuid(my_stat.st_uid) ->pw_name, getgrgid(my_stat.st_gid) -> gr_name, my_stat.st_size, ptm + 4 , pent ->d_name );

	}
	closedir(pdir);
	return 0 ;
}
void time_handle(char* ptm) 
{
	char* pend = ptm + strlen(ptm) ;
	while(*pend != ':')
	{
		pend -- ;
	}
	*pend = '\0' ;
}
void mode2str(mode_t md, char* res)//res.len 11
{
	memset(res, 0, 11);
	if(S_ISREG(md))
	{
		res[0] = '-';
	}else if(S_ISDIR(md))
	{
		res[0] = 'd';
	}else if(S_ISCHR(md))
	{
		res[0] = 'c' ;
	}else if(S_ISBLK(md))
	{
		res[0] = 'b';
	}else if(S_ISFIFO(md))
	{
		res[0] = 'p' ;
	}else if(S_ISLNK(md))
	{
		res[0] = 'l' ;
	}else 
	{
		res[0] = 's' ;
	}
	//usr_r
	if(md & S_IRUSR)
	{
		res[1] = 'r' ;
	}else 
	{
		res[1] = '-' ;
	}
	//usr_w
	if(md & S_IWUSR)
	{
		res[2] = 'w' ;
	}else 
	{
		res[2] = '-' ;
	}
	//usr_x
	if(md & S_IXUSR)
	{
		res[3] = 'x' ;
	}else 
	{
		res[3] = '-' ;
	}
	//grp_r
	if(md & S_IRGRP)
	{
		res[4] = 'r' ;
	}else 
	{
		res[4] = '-' ;
	}
	//grp_w
	if(md & S_IWGRP)
	{
		res[5] = 'w' ;
	}else 
	{
		res[5] = '-' ;
	}

	//grp_x
	if(md & S_IXGRP)
	{
		res[6] = 'x' ;
	}else 
	{
		res[6] = '-' ;
	}
	//oth_r
	if(md & S_IROTH)
	{
		res[7] = 'r' ;
	}else 
	{
		res[7] = '-' ;
	}
	//oth_w
	if(md & S_IWOTH)
	{
		res[8] = 'w' ;
	}else 
	{
		res[8] = '-' ;
	}
	//oth_x
	if(md & S_IXOTH)
	{
		res[9] = 'x' ;
	}else 
	{
		res[9] = '-' ;
	}

}
