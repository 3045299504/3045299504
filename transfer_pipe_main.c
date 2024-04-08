#include"transfer_pipe.h"
#include<errno.h>
int main(){
	//预创建公有管道
	CreatePipe("mkfifo");
	//主端阻塞读取消息
	int fd=open("mkfifo",O_RDONLY);
	while(1){
		char buf[1024];
		int len=read(fd,buf,sizeof(buf));
		char* result;
		result=strtok(buf,":");
		char* data;
		data=strtok(NULL,"\n");
	//如果是login：name形式，主端为从端创建管道文件
		if(strcmp((const char*)result,"login")==0)
		{
			CreatePipe(data);
			printf("%s login sucess\n",data);
		}
	//通过公有管道向主端发送all，主端反馈所有有效用户
		else if(strcmp((const char*)buf,"all")==0){
			write(fd,buf,sizeof(buf));
		}

	//通过公有管道向主端发送quit，主端关闭对应私有管道
		else if(strcmp((const char*)data,"quit")==0){
			DeletePipe(result);
			printf("%s delete success\n",result);
		}
	//如果是dest：data形式，主端根据dest阻塞写
	//如果检测管道文件是否存在
		else if(access(result,F_OK)!=-1){
			int fd_pri=open(result,O_WRONLY);
			if(fd_pri==-1)
				perror("open fail");
			printf("data len=%d\n",len);
			write(fd_pri,data,len);
			close(fd_pri);
		}
	}
		close(fd);
	return 0;
}

