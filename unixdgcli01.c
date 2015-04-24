#include"book.h"

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_un cliaddr,servaddr;
	sockfd=socket(AF_LOCAL,SOCK_DGRAM,0);

	memset(&cliaddr,0,sizeof(cliaddr));
	cliaddr.sun_family=AF_LOCAL;
	strcpy(cliaddr.sun_path,"/tmp/fileXXXXXX");

	bind(sockfd,(struct sockaddr*)&cliaddr,sizeof(cliaddr));

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family=AF_LOCAL;
	strcpy(servaddr.sun_path,"/tmp/tao");

	dg_cli(stdin,sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	exit(0);
}
