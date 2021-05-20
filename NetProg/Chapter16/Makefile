CC = gcc
CFLAGS =
CLIBS = 
CMDS  = serv clnt dup serv2

all : $(CMDS)

serv : sep_serv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clnt : sep_clnt.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

dup : dup.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

serv2 : sep_serv2.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 

