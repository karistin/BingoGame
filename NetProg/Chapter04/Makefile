CC = gcc
CFLAGS =
CLIBS = 
CMDS  = eserver eclient

all : $(CMDS)

eserver :  echo_server.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

eclient : echo_client.c
	$(CC) $(CFLAGS) $^ -o $@  $(CLIBS)

clean :
	rm $(CMDS) core 

