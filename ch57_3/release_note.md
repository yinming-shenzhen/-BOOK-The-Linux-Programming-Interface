# Version

| revision | date       | change description | author        |
| -------- | ---------- | ------------------ | ------------- |
| v 1.0    | 2019-03-01 | initial version    | 4u.ok@163.com |



# Compile and test enviroment

ubuntu 14.04



# Function

us_xfr_sv is the server program, us_xfr_cl is the client program. The client sends text to the server. 



# File description

| description             | filename        |
| ----------------------- | --------------- |
| client souce code file  | us_xfr_cl.c     |
| server source code file | us_xfr_sv.c     |
| the common header file  | us_xfr.h        |
| compile file            | Makefile        |
| this file               | release_note.md |



# How to test 

1. run server program, to accept connection from client .And output to a file "b" 
   (^) ./us_xfr_sv > b & 
2. Input some text to generate a file a 
   (^) cat *.c >  a
3. Run client program which read file a and send the content of a to server. 
   (^) ./us_xfr_cl < a
4. If no bug, there is no difference between a and b.
   (^) diff a b



# New point for me

1. The command "kill %1" to kill a background process.
   (^) jobs -l    	     // to show all background process.
   (^) kill %num 	 // to kill the background process.  