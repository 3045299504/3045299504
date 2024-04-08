#include"transfer_pipe.h"
int main(){
	pid_t pid=fork();
	int fd=open("mkfifo",O_WRONLY);
	NoBlock(fd);
	//主端做出对应操作，从端读取数据，非阻塞读
	int fd_pri=open("P1",O_RDONLY);
	NoBlock(fd);
	if(pid>0){
	while(1){
		char buf_pri[1024];
		read(fd_pri,buf_pri,sizeof(buf_pri));
		printf("data is %s\n",buf_pri);
	}
	}
	else if(pid==0){
	//从端向主端发送消息
	//从端非阻塞写
	while(1){
		char buf[1024];
		fgets(buf,sizeof(buf),stdin);
		write(fd,buf,strlen(buf));
	}
	}
	else {
		perror("fork fail");
		exit(0);
	}
	close(fd);
	close(fd_pri);
	return 0;
}

