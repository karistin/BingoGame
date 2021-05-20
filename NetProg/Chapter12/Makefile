CC = gcc
CFLAGS =
CLIBS = 
CMDS  = select selserv

all : $(CMDS)

select : select.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

selserv : echo_selectserv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 

