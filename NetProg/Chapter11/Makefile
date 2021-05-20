CC = gcc
CFLAGS =
CLIBS = 
CMDS  = pipe1 pipe2 pipe3 serv

all : $(CMDS)

pipe1 : pipe1.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

pipe2 : pipe2.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

pipe3 : pipe3.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

serv : echo_storeserv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core echomsg.txt

