CC = gcc
CFLAGS = 
CLIBS = 
CMDS  = bingo_client bingo_server

all : $(CMDS) 

bingo_client :  bingo_client.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

bingo_server : bingo_server.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread


clean :
	rm $(CMDS) core test.dat