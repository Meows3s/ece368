testE:
	make compile
	./pa4 -e examples/tree0.b

compile:
	clear
	gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -O3 converter.c build.c evaluate.c pa4.c -o pa4
