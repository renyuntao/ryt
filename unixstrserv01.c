#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<netdb.h>
#include<signal.h>
#include<unistd.h>
#include<error.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include"book.h"

int main(int argc,char **argv)
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_un chiaddr,servaddr;

	listenfd=socket(AF_LOCAL,SOCK_STREAM,0);

	unlink("/tmp/ren");
	
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family=AF_LOCAL;
	strcpy(servaddr.sun_path,"/tmp/ren");
	
	bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	listen(listenfd,10);
	signal(SIGCHLD,sig_chld);

	for(;;)
	{
		clilen=sizeof(chiaddr);
		if((connfd=accept(listenfd,(struct sockaddr*)&chiaddr,&clilen))<0)
		{
			if(errno==EINTR)
			{
				continue;
			}
			else
			{
				perror("accept error");
			}
		}

		if((childpid=fork())==0)
		{
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}

}
