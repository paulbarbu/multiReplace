all: subEDIT

subEDIT:
	g++ -Wall -o subEDIT src/*.cpp

clean:
	rm -rf *.{swp,o,i,s}
	find . -type f -name "*~" -exec rm '{}' \;
	rm -rf subEDIT

.PHONY: clean
