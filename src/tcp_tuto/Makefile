CC = gcc
CFLAGS =
CLIBS = 
CMDS  = hserver hclient lopen lread fds

all : $(CMDS)

hserver :  hello_server.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

hclient : hello_client.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

lopen : low_open.c
	$(CC) $(CFLAGS) $^ -o $@ 

lread : low_read.c
	$(CC) $(CFLAGS) $^ -o $@

fds : fd_seri.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core test.dat
