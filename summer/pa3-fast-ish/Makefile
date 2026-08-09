SRC := $(wildcard *.c)
BINS := $(SRC:.c=)

n ?= 10
p ?= 4

default: pa3
	@echo done!

graph: FORCE
	gcc -std=c11 -pedantic -Wvla -Wall -Wshadow -g -O3 makegraph.c -o makegraph
	./makegraph $(n) $(p) graph.txt

pa3: FORCE
	gcc -std=c11 -pedantic -Wvla -Wall -Wshadow -g -O3 -flto $(filter-out makegraph.c, $(wildcard *.c)) -o pa3 -lm

FORCE: ;

clean:
	rm -f graph.txt
	rm -f $(BINS)

memcheck: default
	valgrind --leak-check=full ./pa3 graph.txt

run: default
	./pa3 graph.txt

test: default graph
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa3 graph.txt
