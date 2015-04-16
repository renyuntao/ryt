#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<signal.h>
#define PORT "3490"
#define BACKLOG 10

void sigchld_handler(int s)
{
	while(waitpid(-1,NULL,WNOHANG));  //waitpid() is defined in <sys/wait.h>
}
 void *get_in_addr(struct sockaddr *sa)    //struct sockaddr_in{} and struct sockaddr_in6{} is defined in <netinet/in.h>
 {
 	if(sa->sa_family==AF_INET)               //struct sockaddr{} is defined in <sys/socket.h>
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);    //macro AF_INET is defined in <netinet.h>
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
 }

 int main(void)
 {
 	int sockfd,new_fd;
	struct addrinfo hints,*servinfo,*p;  //struct addrinfo{} is defined in <netdb.h>
	struct sockaddr_storage their_addr;  //struct sockaddr_storage{} is defined in <netinet/in.h>
	socklen_t sin_size;                  //socklen_t is defined in multiple header file,such as <sys/socket.h>
	struct sigaction sa;                 //struct sigaction is defined in <signal.h>
	int yes=1;
	char s[INET6_ADDRSTRLEN];            //macro INET6_ADDRSTRLEN is defined in <netinet/in.h>
	int rv;

	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE;

	if((rv=getaddrinfo(NULL,PORT,&hints,&servinfo))!=0)
	{
		fprintf(stderr,"getaddrinfo:%s\n",gai_strerror(rv));	
		return 1;
	}
	for(p=servinfo;p!=NULL;p=p->ai_next)
	{
		if((sockfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))==-1)
		{
			perror("server:socket");
			continue;
		}

		if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1)
		{
			perror("setsockopt");
			exit(1);
		}

		if(bind(sockfd,p->ai_addr,p->ai_addrlen)==-1)
		{
			close(sockfd);     //close() is defined in <unistd.h>
			perror("server:bind");
		}
		break;
	}

	if(p==NULL)
	{
		fprintf(stderr,"server:failed to bind\n");
		return 2;
	}

	freeaddrinfo(servinfo);

	if(listen(sockfd,BACKLOG)==-1)
	{
		perror("listen");
		exit(1);
	}

	sa.sa_handler=sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=SA_RESTART;

	if(sigaction(SIGCHLD,&sa,NULL)==-1)
	{
		perror("sigaction");
		exit(1);
	}

	printf("server:waiting for connections...");

	while(1)
	{
		sin_size=sizeof(their_addr);
		new_fd=accept(sockfd,(struct sockaddr*)&their_addr,&sin_size);
		if(new_fd==-1)
		{
			perror("accept");	
			continue;
		}

		inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr*)&their_addr),s,sizeof(s));
		
		printf("server:get connnection from %s\n",s);

		if(!fork())   //at child process
		{
			close(sockfd);	
			if(send(new_fd,"Hello World!",13,0)==-1)
			{
				perror("send");
			}
			close(new_fd);
			exit(0);
		}
		close(new_fd);
	}
	return 0;
 }


