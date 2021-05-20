CC = gcc
CFLAGS =
CLIBS = 
CMDS  = oob_send oob_recv peek_send peek_recv wv rv

all : $(CMDS)

oob_send : oob_send.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

oob_recv : oob_recv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

peek_send : peek_send.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

peek_recv : peek_recv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

wv : writev.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

rv : readv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 

