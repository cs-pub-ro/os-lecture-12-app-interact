CPPFLAGS = -I../../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g

.PHONY: all clean

all: signal_sender signal_receiver signalfd_receiver

signal_sender: signal_sender.o

signal_sender.o: signal_sender.c ../../utils/utils.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

signal_receiver: signal_receiver.o

signal_receiver.o: signal_receiver.c ../../utils/utils.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

signalfd_receiver: signalfd_receiver.o

signalfd_receiver.o: signalfd_receiver.c ../../utils/utils.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f signal_sender.o signal_sender
	-rm -f signal_receiver.o signal_receiver
	-rm -f signalfd_receiver.o signalfd_receiver
