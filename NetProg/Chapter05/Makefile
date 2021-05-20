CC = gcc
CFLAGS =
CLIBS = 
CMDS  = echo_client2 echo_server opserver opclient

all : $(CMDS)

echo_client2 : echo_client2.c  
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

echo_server :echo_server.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

opserver :  op_server.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

opclient : op_client.c
	$(CC) $(CFLAGS) $^ -o $@  $(CLIBS)

clean :
	rm $(CMDS) core 

