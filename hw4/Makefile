default:
	clear
	gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -O3 *.c -o pa4

testE: default
	./pa4 -e examples/tree0.b

testB: default
	./pa4 -b examples/ops2.b outputs/tree2.b
	diff examples/tree2.b outputs/tree2.b
