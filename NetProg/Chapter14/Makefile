CC = gcc
CFLAGS =
CLIBS = 
CMDS  = news_sender news_receiver news_sender_brd news_receiver_brd

all : $(CMDS)

news_sender : news_sender.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

news_receiver : news_receiver.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

news_sender_brd : news_sender_brd.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

news_receiver_brd : news_receiver_brd.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean :
	rm $(CMDS) core 

