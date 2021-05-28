CC = gcc
CFLAGS = 
CLIBS = 
CMDS  = bingo_client bingo_server test

all : $(CMDS) 

bingo_client :  bingo_client.c
	$(CC) $(CFLAGS) $^ -o $@ 

bingo_server : bingo_server.c
	$(CC) $(CFLAGS) $^ -o $@ 

test : test.c 
	$(CC) $(CFLAGS) $^ -o $@ 

clean :
	rm $(CMDS) core test.dat