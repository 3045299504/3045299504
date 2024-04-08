#include"transfer_pipe.h"
void CreatePipe(char* pathname)
{
	int n=mkfifo(pathname,0664);
	if(n<0){
		perror("mkfifo fail");
		exit(0);
	}
}
void DeletePipe(char* pathname)
{
	int n=unlink((const char*)pathname);
	if(n!=0){
		perror("unlink fail");
		exit(0);
	}
}
void  NoBlock(int fd)
{
	int flag;
	flag=fcntl(fd,F_GETFL);
	flag|=O_NONBLOCK;
	fcntl(fd,F_SETFL,flag);
}



