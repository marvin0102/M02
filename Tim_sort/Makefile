CC = gcc
CFLAGS = -O1 -g -Wall


OBJS := main.o tim_sort.o

all: Tsorttest

Tsorttest: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

clean:
	rm -f $(OBJS)
	rm -f *.dSYM
	rm -f Tsorttest
	rm -f .*.o.d