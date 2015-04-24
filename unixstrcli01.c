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
#define max(a,b) (a>b?a:b)

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_un servaddr;

	sockfd=socket(AF_LOCAL,SOCK_STREAM,0);

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family=AF_LOCAL;
	strcpy(servaddr.sun_path,"/tmp/ren");

	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	str_cli(stdin,sockfd);
	exit(0);
}
