#include"book.h"

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_un servaddr,cliaddr;

	sockfd=socket(AF_LOCAL,SOCK_DGRAM,0);

	unlink("/tmp/tao");
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family=AF_LOCAL;
	strcpy(servaddr.sun_path,"/tmp/tao");

	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	dg_echo(sockfd,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	return 0;
}
