CC = gcc
CFLAGS =
CLIBS = 
CMDS  = hserver hclient

all : $(CMDS)

hserver : tcp_server.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

hclient : tcp_client.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

lopen : low_open.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

lread : low_read.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

fds : fd_seri.c
	$(CC) $(CFLAGS) $^ -o $@  $(CLIBS)

clean :
	rm $(CMDS) core

