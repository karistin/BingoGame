CC = gcc
CFLAGS = 
CLIBS = 
CMDS  = bingo_client bingo_server

all : $(CMDS) 

bingo_client :  bingo_client.c
	$(CC) $(CFLAGS) $^ -o $@ 

bingo_server : bingo_server.c
	$(CC) $(CFLAGS) $^ -o $@ 


clean :
	rm $(CMDS) core test.dat