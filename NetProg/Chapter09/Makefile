CC = gcc
CFLAGS =
CLIBS = 
CMDS  = socktype getbuf setbuf reuseadr_eserver

all : $(CMDS)

socktype : sock_type.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

getbuf : get_buf.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

setbuf : set_buf.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

reuseadr_eserver : reuseadr_eserver.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 
