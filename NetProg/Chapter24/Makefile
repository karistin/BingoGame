CC = gcc
CFLAGS =
CLIBS = -pthread
CMDS  = webserv_linux

all : $(CMDS)

webserv_linux : webserv_linux.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 

