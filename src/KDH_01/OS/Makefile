CC = gcc
CFLAGS =
CLIBS =
CMDS = multi_process multi_process_2 multi_process_3 multi_thread_mutex multi_thread_mutex_ver2 multi_thread time_test

all : $(CMDS)

multi_thread_mutex : multi_thread_mutex.c
	$(CC) -O0 $(CFLAGS) $^ -o $@ -lpthread

multi_thread_mutex_ver2 : multi_thread_mutex_ver2.c
	$(CC) -O0 $(CFLAGS) $^ -o $@ -lpthread

multi_thread : multi_thread.c
	$(CC) -O0 $(CFLAGS) $^ -o $@ -lpthread

multi_process : multi_process.c
	$(CC) -O0 $(CFLAGS) $^ -o $@ -lpthread
	
multi_process_2 : multi_process_2.c
	$(CC) -O0 $(CFLAGS) $^ -o $@ -lpthread

multi_process_3 : multi_process_3.c
	$(CC) -O0 $(CFLAGS) $^ -o $@ -lpthread
	
time_test : time_test.c
	$(CC) -O0 $(CFLAGS) $^ -o $@

clean :
	rm $(CMDS) core