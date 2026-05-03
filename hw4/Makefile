pa4:
	clear
	gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -O3 *.c -o pa4

testE: pa4
	valgrind --leak-check=full ./pa4 -e examples/tree0.b outputs/tree0.b

testB: pa4
	valgrind --leak-check=full ./pa4 -b examples/ops2.b outputs/tree2.b
	diff examples/tree2.b outputs/tree2.b

zip:
	zip pa4.zip *.c *.h Makefile
