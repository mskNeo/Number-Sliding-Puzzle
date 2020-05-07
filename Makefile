CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -g3

all:    Nine20 testHash

Deque.o:   Deque.h

Hash.o:    Hash.h 

error.o:   error.h


#####
# Instructions to make Nine20
#####

Nine20: Nine20.o error.o Deque.o Hash.o 
	${CC} ${CFLAGS} -o $@ $^

Nine20.o: Nine20.h Deque.h Hash.h error.h 

testHash: testHash.o Hash.o 
	${CC} ${CFLAGS} -o $@ $^

testHash.o: Hash.h

clean:
	rm -f Nine20 testHash *.o
