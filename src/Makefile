CC=gcc
VV=valgrind
CFLAGS=-lmagic -o mr -std=c99 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes
VFLAGS=--track-fds=yes --log-file=vgrind.dbg --tool=memcheck --leak-check=yes --show-reachable=yes ./mr
DBGFLAGS=-g
OBJS=main.o functions.o

all: multiReplacer

multiReplacer: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS)

debug: $(OBJS)
	$(CC) $(DBGFLAGS) $(OBJS:.o=.c) $(CFLAGS)
	#run with/without replacements to be made
	#run with words/letters for replacements/replacees

	#$(VV) $(VFLAGS)
	#$(VV) $(VFLAGS) -p
	#$(VV) $(VFLAGS) -p -
	#$(VV) $(VFLAGS) -p-
	#$(VV) $(VFLAGS) -p test
	#$(VV) $(VFLAGS) -c
	#$(VV) $(VFLAGS) -c -
	#$(VV) $(VFLAGS) -c ./config/default.ini
	#$(VV) $(VFLAGS) -c config/default.ini
	#$(VV) $(VFLAGS) -c test
	#$(VV) $(VFLAGS) -c ./test
	#$(VV) $(VFLAGS) -l
	#$(VV) $(VFLAGS) -l -
	#$(VV) $(VFLAGS) -l asd
	#$(VV) $(VFLAGS) -c inexistent_file
	#$(VV) $(VFLAGS) -c empty_file
	#$(VV) $(VFLAGS) -c cfg_test
	#$(VV) $(VFLAGS) -p empty_dir
	#$(VV) $(VFLAGS) -p testdir -l test
	#$(VV) $(VFLAGS) -p testdir/testdir2/test_file -l test

	#TODO:
	#$(VV) $(VFLAGS) -p ./test #check that overlapping

%.o: src/%.c
	$(CC) -c $*.c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.{swp,o,i,s,out,dbg}
	find . -type f -name "*~" -exec rm '{}' \;
	rm -rf mr
