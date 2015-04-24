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

int main(int argc,char **argv)
{
	int sockfd;
	socklen_t len;
	struct sockaddr_un addr1,addr2;

	if(argc!=2)
	{
		fprintf(stderr,"usage:unixbind <pathname>\n");
		return 1;
	}

	sockfd=socket(AF_LOCAL,SOCK_STREAM,0);

	unlink(argv[1]);

	memset(&addr1,0,sizeof(addr1));
	addr1.sun_family=AF_LOCAL;
	strncpy(addr1.sun_path,argv[1],sizeof(addr1.sun_path)-1);
	bind(sockfd,(struct sockaddr*)&addr1,SUN_LEN(&addr1));

	len=sizeof(addr2);
	getsockname(sockfd,(struct sockaddr*)&addr2,&len);
	printf("bound name=%s,returned len=%d\n",addr2.sun_path,len);
	exit(0);
}
