CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes
OBJS=main.o functions.o

all: multiReplacer

multiReplacer: $(OBJS)
	$(CC) -o mr $(OBJS) $(CFLAGS)

debug: $(OBJS)
	$(CC) -o mr -g $(OBJS:.o=.c) $(CFLAGS)
	valgrind --track-fds=yes --log-file=vgrind.dbg --tool=memcheck --leak-check=yes --show-reachable=yes ./mr

%.o: src/%.c
	$(CC) -c $*.c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.{swp,o,i,s,out}
	find . -type f -name "*~" -exec rm '{}' \;
	rm -rf mr
