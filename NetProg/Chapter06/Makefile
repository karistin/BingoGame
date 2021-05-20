CC = gcc
CFLAGS =
CLIBS = 
CMDS  = userver uclient host1 host2 uecho_con_client

all : $(CMDS)

userver : uecho_server.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

uclient : uecho_client.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

host1 : bound_host1.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

host2 : bound_host2.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

uecho_con_client : uecho_con_client.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 
