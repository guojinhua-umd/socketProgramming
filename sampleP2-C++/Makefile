CFLAGS= -g -std=c++11 -pthread
LDFLAGS= #-lsocket -lnsl
LDFLAGS1= -pthread #-lsocket -lnsl
CC=g++

all: sclient multiThreadServer

# To make an executable
sclient: sclient.o 
	$(CC) $(LDFLAGS) -o sclient sclient.o
 
multiThreadServer: multiThreadServer.o
	$(CC) $(LDFLAGS1) -o multiThreadServer multiThreadServer.o

# To make an object from source
.c.o:
	$(CC) $(CFLAGS) -c $*.c

# clean out the dross
clean:
	-rm sclient multiThreadServer *.o core 

