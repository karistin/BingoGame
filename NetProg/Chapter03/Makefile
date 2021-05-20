CC = gcc
CFLAGS =
CLIBS = 
CMDS  = conv addr aton ntoa

all : $(CMDS)

conv :  endian_conv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

addr : inet_addr.c
	$(CC) $(CFLAGS) $^ -o $@  $(CLIBS)

aton : inet_aton.c
	$(CC) $(CFLAGS) $^ -o $@  $(CLIBS)

ntoa : inet_ntoa.c
	$(CC) $(CFLAGS) $^ -o $@  $(CLIBS)

clean :
	rm $(CMDS) core 

