/*
	date: 2019-2-28

	bind的注意事项：
	1. 地址必须是一个保存在的文件，否则会bind失败

*/

#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int main(int argc, char* argv[])
{
	//the file shouldn't be existed. If no, bind: Address already in use
	const char* SOCKNAME="/tmp/mysock";
	int sfd;
	struct sockaddr_un addr;

	printf("[%s %d]\n", __FUNCTION__, __LINE__);

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(-1 == sfd)
	{
		perror("socket:");
		return 1;
	}

	memset(&addr, 0x00, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKNAME, sizeof(addr.sun_path)-1);

	if(bind(sfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un))==-1)
	{
		perror("bind");
		return 1;
	}

	remove(SOCKNAME);

	return 0;
}
