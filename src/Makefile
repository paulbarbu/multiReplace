CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes
OBJS=main.o functions.o

all: subEDIT

subEDIT: $(OBJS)
	$(CC) -o subEDIT $(OBJS) $(CFLAGS)

%.o: src/%.c
	$(CC) -c $*.c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.{swp,o,i,s}
	find . -type f -name "*~" -exec rm '{}' \;
	rm -rf subEDIT
