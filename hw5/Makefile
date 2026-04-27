default:
	clear
	gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -g -O3 *.c -o pa5

run: default
	./pa5 examples/river.in0 out1 out2

mem: default
	valgrind --leak-check=full ./pa5 examples/river.in0 out1 out2

debug: default
	gdb ./pa5
