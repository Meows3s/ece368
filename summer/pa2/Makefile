SRC := $(wildcard *.c)
BINS := $(SRC:.c=)

n ?= 10
min ?= -100
max ?= 100

default: pa2
	@echo done!

pointGen: FORCE
	gcc -std=c11 -pedantic -Wvla -Wall -Wshadow -g -O3 pointGen.c -o pointGen
	./pointGen $(n) $(min) $(max) points.txt

pa2: FORCE
	gcc -std=c11 -pedantic -Wvla -Wall -Wshadow -g -O3 $(filter-out pointGen.c, $(wildcard *.c)) *.h -o pa2 -lm

FORCE: ;

clean:
	rm -f points.txt
	rm -f $(BINS)

memcheck: default
	valgrind --leak-check=full ./pa2

run: default
	./pa2 points.txt

test: default pointGen
	valgrind --leak-check=full ./pa2 points.txt
