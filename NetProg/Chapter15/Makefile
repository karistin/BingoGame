CC = gcc
CFLAGS =
CLIBS = 
CMDS  = syscpy stdcpy desto todes echo_stdserv echo_stdclnt

all : $(CMDS)

syscpy : syscpy.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

stdcpy : stdcpy.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

desto : desto.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

todes : todes.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

echo_stdserv : echo_stdserv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

echo_stdclnt : echo_stdclnt.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core cpy.txt data.dat

