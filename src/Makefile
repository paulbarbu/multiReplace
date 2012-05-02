CC=gcc
VV=valgrind
CFLAGS=-o mr -std=c99 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes
VFLAGS=--track-fds=yes --log-file=vgrind.dbg --tool=memcheck --leak-check=yes --show-reachable=yes ./mr
DBGFLAGS=-g
OBJS=main.o functions.o

all: multiReplacer

multiReplacer: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS)

debug: $(OBJS)
	$(CC) $(DBGFLAGS) $(OBJS:.o=.c) $(CFLAGS)
	#$(VV) $(VFLAGS)
	#$(VV) $(VFLAGS) -p
	#$(VV) $(VFLAGS) -p -
	#$(VV) $(VFLAGS) -p-
	#$(VV) $(VFLAGS) -p test
	#$(VV) $(VFLAGS) -p ./test #check that overlapping
	#$(VV) $(VFLAGS) -c
	#$(VV) $(VFLAGS) -c -
	#$(VV) $(VFLAGS) -c ./config/default.ini
	#$(VV) $(VFLAGS) -c config/default.ini
	#$(VV) $(VFLAGS) -c test
	#$(VV) $(VFLAGS) -c ./test
	#test the -l part

%.o: src/%.c
	$(CC) -c $*.c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.{swp,o,i,s,out,dbg}
	find . -type f -name "*~" -exec rm '{}' \;
	rm -rf mr
