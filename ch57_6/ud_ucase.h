#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

#define BUF_SIZE 10	/* Maximum size of messages exchanged 
			   between client to server */
#define SV_SOCK_PATH "/tmp/ud_case"

