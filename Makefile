all: subEDIT

subEDIT: main.o functions.o
	g++ -Wall *.o -o subEDIT

main.o: src/main.cpp
	g++ -Wall -c src/main.cpp

functions.o: src/functions.cpp
	g++ -Wall -c src/functions.cpp

.PHONY: clean

clean:
	rm -rf *.{swp,o,i,s}
	find . -type f -name "*~" -exec rm '{}' \;
	rm -rf subEDIT
