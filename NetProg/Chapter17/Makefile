CC = gcc
CFLAGS =
CLIBS = 
CMDS  = echo_epollserv echo_EPLTserv echo_client echo_EPETserv

all : $(CMDS)

echo_epollserv : echo_epollserv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

echo_EPLTserv : echo_EPLTserv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

echo_client : echo_client.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

echo_EPETserv : echo_EPETserv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 

