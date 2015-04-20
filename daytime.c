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
#define MAXLINE 4096

int main(int argc,char **argv)
{
	int t;
	int sockfd,n;
	char recvline[MAXLINE];
	struct sockaddr_in servaddr;

	if(argc!=2)
	{
		fprintf(stderr,"usage:a.out <IPaddress>");
	}
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
		perror("sock error:");
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(13);    //the port of 13 is the daytime server
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<0)
	{
		printf("Result:%d\n",t);
		perror("inet_pton error ");
	}

	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		perror("connect error");
	}
	
	while((n=read(sockfd,recvline,MAXLINE-1))>0)
	{
		recvline[n]=0;   //null terminate
		if(fputs(recvline,stdout)==EOF)
		{
			perror("fputs error");
		}
	}
	if(n<0)
	{
		perror("read error");
	}
	exit(0);
}
