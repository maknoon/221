CC=g++
CFLAGS=-Wall -O3
PROG0=runway
PROG1=lq
OBJS0=runway.o LQueue.o
OBJS1=LQueue_driver.o LQueue.o 

all:	runway lq

runway: $(OBJS0)
	$(CC) -o $(PROG0) $(OBJS0)
	
lq:	$(OBJS1)
	$(CC) -o $(PROG1) $(OBJS1)

.C.o:
	$(CC) $(CFLAGS) -c $*.C
	
runway.o:		runway.C LQueue.o LQueue.h

LQueue_driver.o:	LQueue_driver.C LQueue.o LQueue.h

LQueue.o:		LQueue.h


clean:
	rm -f *.o runway lq runway.log
