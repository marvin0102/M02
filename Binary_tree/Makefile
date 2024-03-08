CC = gcc
CFLAGS = -O1 -g -Wall


OBJS := main.o B_tree.o

all: CBTtest

CBTtest: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

clean:
	rm -f $(OBJS)
	rm -f *.dSYM
	rm -f CBTtest
	rm -f .*.o.d