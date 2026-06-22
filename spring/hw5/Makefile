pa5:
	clear
	gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -g -O3 *.c -o pa5

run: pa5
	./pa5 examples/river.in0 out1.txt out1_2.txt
	diff examples/river.in0.out2 out1_2.txt

run2: pa5
	./pa5 examples/river.in1 out2.txt out2_2.txt
	diff examples/river.in1.out2 out2_2.txt

mem: default
	valgrind --leak-check=full ./pa5 examples/river.in0 out1 out2

debug: default
	gdb ./pa5 run
