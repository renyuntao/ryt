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
#include<errno.h>
#define MAXLINE 100
#define max(a,b) (a>b?a:b)

void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	pid=wait(&stat);
	printf("child %d terminated\n",pid);
	return;
}

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n=read(sockfd,buf,MAXLINE))>0)
	{
		write(sockfd,buf,n);
	}
	if(n<0&&errno==EINTR)
	{
		goto again;
	}
	else if(n<0)
	{
		perror("str_echo:read error");
	}
}

void str_cli(FILE *fp,int sockfd)
{
	int maxfdp1,stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof=0;
	FD_ZERO(&rset);
	for(;;)
	{
		if(stdineof==0)
			FD_SET(fileno(fp),&rset);
		FD_SET(sockfd,&rset);
		maxfdp1=max(fileno(fp),sockfd)+1;
		select(maxfdp1,&rset,NULL,NULL,NULL);

		if(FD_ISSET(sockfd,&rset))
		{
			if((n=read(sockfd,buf,MAXLINE))==0)
			{
				if(stdineof==1)
				{
					return;
				}
				else
					perror("str_cli:server terminated prematurely");
			}
			write(fileno(stdout),buf,n);
		}

		if(FD_ISSET(fileno(fp),&rset))
		{
			if((n=read(fileno(fp),buf,MAXLINE))==0)
			{
				stdineof=1;
				shutdown(sockfd,SHUT_WR);
				FD_CLR(fileno(fp),&rset);
				continue;
			}
			write(sockfd,buf,n);
		}
	}
}

void dg_echo(int sockfd,struct sockaddr *pcliaddr,socklen_t client)
{
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	for(;;)
	{
		len=client;
		n=resvfrom(sockfd,mesg,MAXLINE,pcliaddr,&len);
		sendto(sockfd,mesg,n,0,pcliaddr,len);
	}
}
