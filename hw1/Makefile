default:
	clear
	gcc -std=c99 -Wall -Wshadow -Wvla -pedantic *.c *.h -g -o pa1

run: default
	./pa1 -a examples/15.b outputs/15sa.b
	diff examples/15sa.b outputs/15sa.b

debug: default
	valgrind --leak-check=full -s ./pa1 -a examples/15.b outputs/15sa.b
