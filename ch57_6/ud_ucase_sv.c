#include "ud_ucase.h"

int 
main(int argc, char* argv[])
{
	int len;
	int j;
	int numBytes;
	char buf[BUF_SIZE];
	int sfd;
	struct sockaddr_un svaddr, claddr;

	/*Create the server socket and bind it to a well known address*/

	sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(-1 == sfd)
	{
		perror("socket");
		return 1;
	}

	if(remove(SV_SOCK_PATH)==-1 && errno!=ENOENT)
	{
		perror("remove:");
		return 1;
	}

	memset(&svaddr, 0x00, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path)-1);
	
	if(bind(sfd, (struct sockaddr*)&svaddr, sizeof(struct sockaddr_un))==-1)
	{
		perror("bind:");
		return 1;
	}

	/*Receive message, convert to uppercase, and return to client*/
	for(;;)
	{
		len = sizeof(struct sockaddr_un);
		/*
		ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
		                        struct sockaddr *src_addr, socklen_t *addrlen);
		*/
		numBytes = recvfrom(sfd, buf, BUF_SIZE, 0, 
			(struct sockaddr*)&claddr, &len);
		if(numBytes == -1)
		{
			perror("recvfrom");
			return 1;
		}

		for(j=0; j<numBytes; j++)
		{
			buf[j]=toupper((unsigned char)buf[j]);
		}
		/*
		ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
		                      const struct sockaddr *dest_addr, socklen_t addrlen);
		*/
		if(sendto(sfd, buf, numBytes, 0, (struct sockaddr*)&claddr,
			  len)!=numBytes)
		{
			perror("sendto:");
			return 1;
		}
	}

	return 0;
}
