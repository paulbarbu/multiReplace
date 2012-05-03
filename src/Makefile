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
	#$(VV) $(VFLAGS) -p ./test #check that overlapping TODO
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

	#TODO:
	#$(VV) $(VFLAGS) -p testdir -l test #run when there are replacements to be made and when not, too
	#$(VV) $(VFLAGS) -p testdir/test_file -l test # invalid read of size 1
	# test with full word to replace not just one letter replacee and
	# replacements

%.o: src/%.c
	$(CC) -c $*.c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.{swp,o,i,s,out,dbg}
	find . -type f -name "*~" -exec rm '{}' \;
	rm -rf mr
