CC = gcc
CFLAGS = -D_REENTRANT
CLIBS = -pthread
CMDS  = thread1 thread2 thread3 thread4 mutex semaphore chat_serv chat_clnt

all : $(CMDS)

thread1 : thread1.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

thread2 : thread2.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

thread3 : thread3.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

thread4 : thread4.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

mutex : mutex.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

semaphore : semaphore.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

chat_serv : chat_serv.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

chat_clnt : chat_clnt.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 

