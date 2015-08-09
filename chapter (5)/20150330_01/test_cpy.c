#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
int main(int argc, char* argv[])//file_name
{
	return 0 ;
}
/*
   void test1()
   {
   int fd1 = open(argv[1], O_RDONLY);

   int fd2 ;
   int readn ;

   fd2 = fd1 ;

   close(fd1);
   char buf[1024] = "" ;

   readn = read(fd2, buf, 1023);
   if(readn == -1)
   {
   perror("read:");
   }

   printf(" %s:, %d\n",  buf, readn);

   }
   void test2()
   {
   int fd1 = open(argv[1], O_RDONLY);

   int fd2 ;
   int readn ;

   fd2 = dup(fd1) ;
   printf("fd1: %d, fd2: %d\n", fd1, fd2);
   close(fd1);
   char buf[1024] = "" ;

   readn = read(fd2, buf, 1023);
   if(readn == -1)
   {
   perror("read:");
   }

   printf(" %s:, %d\n",  buf, readn);
   close(fd2);
   }
   void test3()
   {
   int fd1 = open(argv[1], O_RDONLY);

   int fd2 ;
   int readn ;
   close(0);
   fd2 = dup(fd1) ;
   printf("fd1: %d, fd2: %d\n", fd1, fd2);
   close(fd1);
   char buf[1024] = "" ;

//	readn = read(fd2, buf, 1023);
fgets(buf, 1024, stdin);
if(readn == -1)
{
perror("read:");
}
printf(" %s:, %d\n",  buf, readn);
close(fd2);
}
void test4()
{

int fd1 = open(argv[1], O_WRONLY);

int fd2 ;
int readn ;
fd2 = dup2(fd1, 1);// close(0)  dup(fd1)
printf("fd1: %d, fd2: %d\n", fd1, fd2);
//	close(fd1);
char buf[1024] = "" ;

//	readn = read(fd2, buf, 1023);
fgets(buf, 1024, stdin);
if(readn == -1)
{
	perror("read:");
}
//	fprintf( stdout," %s:, %d\n",  buf, readn);
write(1, buf, strlen(buf));

close(fd2);
}
}
void test5()
{
	int fd1 = open(argv[1], O_RDONLY);

	int fd2 ;
	int readn ;
	fd2 = dup2(fd1, 0);// close(0)  dup(fd1)
	printf("fd1: %d, fd2: %d\n", fd1, fd2);
	//	close(fd1);
	char buf[1024] = "" ;

	//	readn = read(fd2, buf, 1023);
	fgets(buf, 1024, stdin);
	if(readn == -1)
	{
		perror("read:");
	}
	//	fprintf( stdout," %s:, %d\n",  buf, readn);
	write(1, buf, strlen(buf));

	close(fd2);
} 
void test6()
{
	int fd = fileno(stdin);
	char buf[1024] = "" ;
	read(fd, buf, 1023);

	write(1, buf, strlen(buf));
} 
void test7()
{
	FILE* fp = fdopen(1, "w");
	char* p = "hello world!\n";

	fprintf(fp, "%s\n", p);

} */
