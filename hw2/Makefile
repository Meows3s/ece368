pa2:
	clear
	gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic *.c -o pa2

clean:
	rm pa2

debug: pa2
	valgrind -s --leak-check=full ./pa2 examples/3.pr outputs/3.po outputs/3.dim outputs/3.pck

run3: pa2
	./pa2 examples/3.pr outputs/3.po outputs/3.dim outputs/3.pck
	diff examples/3.po outputs/3.po
	diff examples/3.dim outputs/3.dim
	diff examples/3.pck outputs/3.pck

run8: pa2
	./pa2 examples/8.pr outputs/8.po outputs/8.dim outputs/8.pck
	diff examples/8.po outputs/8.po
	diff examples/8.dim outputs/8.dim
	diff examples/8.pck outputs/8.pck



test1k: default
	./pa2 examples/1K.pr outputs/1K.po outputs/1K.dim outputs/1K.pck
	
