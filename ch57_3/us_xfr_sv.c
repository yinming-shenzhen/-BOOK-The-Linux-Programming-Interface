#include "us_xfr.h"
#include <errno.h>

#define BACKLOG 5

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

	if(remove(SV_SOCK_PATH)==-1 && errno != ENOENT)
	{
		perror("remove:");
		return 1;
	}

	memset(&addr, 0x00, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);
	if(bind(sfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un))==-1)
	{
		perror("bind:");
		return 1;
	}

	if(listen(sfd, BACKLOG)==-1)
	{
		perror("listen");
		return 1;
	}

	for(;;)	/*Handle client connections iteratively*/
	{
		/* 	Accept a connection, The connection is returned on a new 
			socket, 'cfd'; the listening socket 'sfd' remains open 
			and can be used to accept further connections. */

		cfd = accept(sfd, NULL, NULL);
		if(-1 == cfd)
		{
			perror("accept");
			return 1;
		}

		/* 	Transfer data from connected socket to stdout until EOF */
		while((numRead = read(cfd, buf, BUF_SIZE)) > 0)
		{
			if(write(STDOUT_FILENO, buf, numRead) != numRead)
			{
				perror("write:");
				return 1;
			}
		}

		if(numRead == -1)
		{
			perror("read");
			return 1;
		}

		if(close(cfd) == -1)
		{
			perror("close");
			return 1;
		}

	}

	return 0;
}
