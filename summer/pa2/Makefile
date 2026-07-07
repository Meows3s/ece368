SRC := $(filter-out pointGen.c, $(wildcard *.c))
	
n ?= 10
min ?= -100
max ?= 100

default: pa2
	@echo done!

pointGen: FORCE
	gcc -std=c11 -pedantic -Wvla -Wall -Wshadow -g -O3 pointGen.c -o pointGen
	./pointGen $(n) $(min) $(max) points.txt

pa2: FORCE
	gcc -std=c11 -pedantic -Wvla -Wall -Wshadow -g -O3 $(SRC) *.h -o pa2

FORCE: ;

clean:
	rm -f points.txt
	rm -f *.out

memcheck: default
	valgrind --leak-check=full ./pa2

run: default
	./pa2
