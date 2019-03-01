#include "us_xfr.h"
#include <errno.h>


int
main(int argc, char* argv[])
{
	struct sockaddr_un addr;
	int sfd, cfd;
	ssize_t numRead;
	char buf[BUF_SIZE];

	printf("[%s %d]\n", __FUNCTION__, __LINE__);

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(-1 == sfd)
	{
		perror("socket:");
		return 1;
	}

	/* Construct server socket address, bind socket to it,
	   and make this a listening socket */

	memset(&addr, 0x00, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);
	if(connect(sfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un))==-1)
	{
		perror("connect:");
		return 1;
	}
	
	/*	Copy stdin to socket */
	while((numRead=read(STDIN_FILENO, buf, BUF_SIZE))>0)
	{
		if(write(sfd, buf, numRead) != numRead)
		{
			perror("write");
			return 1;
		}
	}

	if(-1 == numRead)
	{
		perror("read");
		return 1;
	}

	return 0;
}
