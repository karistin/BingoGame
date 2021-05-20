CC = gcc
CFLAGS =
CLIBS = 
CMDS  = hostname hostaddr

all : $(CMDS)

hostname : gethostbyname.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

hostaddr : gethostbyaddr.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 
