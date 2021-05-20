CC = gcc
CFLAGS =
CLIBS = 
CMDS  = fserver fclient

all : $(CMDS)

fserver : file_server.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

fclient : file_client.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core receive.dat
