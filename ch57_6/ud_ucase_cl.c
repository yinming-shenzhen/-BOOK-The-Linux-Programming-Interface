#include "ud_ucase.h"

int 
main(int argc, char* argv[])
{
	struct sockaddr_un svaddr, claddr;
	int numBytes;
	int msgLen;
	char resp[BUF_SIZE];
	int sfd, j;

	if(argc < 2 || strcmp(argv[1], "--help")==0)
	{
		printf("%s msg...", argv[0]);
		return 1;
	}


	/* Create client socket, bind to unique pathname(based on PID)*/

	sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sfd == -1)
	{
		perror("socket:");
		return 1;
	}

	memset(&claddr, 0x00, sizeof(struct sockaddr_un));
	claddr.sun_family = AF_UNIX;
	snprintf(claddr.sun_path, sizeof(claddr.sun_path),
		 "/tmp/ud_ucase_cl.%ld", (long)getpid());

	if(bind(sfd, (struct sockaddr*)&claddr, sizeof(struct sockaddr_un))==-1)
	{
		perror("bind:");
		return 1;
	}

	/* Construct server address*/
	
	memset(&svaddr, 0x00, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path)-1);

	/* Send message to server; echo responses on stdout */

	for(j=1; j<argc;j++)
	{
		msgLen=strlen(argv[j]);
		/*ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
		                      const struct sockaddr *dest_addr, socklen_t addrlen);*/
		if(sendto(sfd, argv[j], msgLen, 0, (struct sockaddr*)&svaddr,
		          sizeof(struct sockaddr_un)) != msgLen)
		{
			perror("sendto:");
			return 1;
		}

		/*ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
		                        struct sockaddr *src_addr, socklen_t *addrlen);*/
		numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
		if(numBytes == -1)
		{
			perror("recvfrom:");
			return 1;
		}

		printf("Response %d: %.*s\n", j, numBytes, resp);
	}

	return 0;
}
