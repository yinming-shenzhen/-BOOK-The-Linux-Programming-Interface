# Version

| revision | date       | change description | author        |
| -------- | ---------- | ------------------ | ------------- |
| v 1.0    | 2019-03-01 | initial version    | 4u.ok@163.com |



# Compile and test enviroment

ubuntu 14.04



# Function

Exercise to use recvfrom and sendto



ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,  

​				struct sockaddr *src_addr, socklen_t *addrlen);

src_addr, 用于获取客户端的地址，如果不关心，可以写NULL



ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, 

​				const struct sockaddr *dest_addr, socklen_t addrlen);

dest_addr, 发送的目标地址必须填写


# File description

| description             | filename        |
| ----------------------- | --------------- |
| client souce code file  | ud_ucase_cl.c   |
| server source code file | ud_ucase_sv.c   |
| the common header file  | us_ucase.h      |
| compile file            | Makefile        |
| this file               | release_note.md |



# How to test 

1. run server program, to accept connection from client .
   (^) ./ud_ucase_sv & 
2. Run client program to send a message and get the echo from server
   (^) ./ud_ucase_cl hello



# New point for me

1. printf("Response %d: %.*s\n", j, numBytes, resp);
   **%.star** and a number to set the width of the string.
2. 