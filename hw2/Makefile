default:
	clear
	gcc *.c *.h -g -o pa2

debug: default
	valgrind -s --leak-check=full ./pa2 examples/3.pr outputs/3.po outputs/3.dim outputs/3.pck

run: default
	./pa2 examples/3.pr outputs/3.po outputs/3.dim outputs/3.pck
	diff examples/3.po outputs/3.po
	diff examples/3.dim outputs/3.dim
	diff examples/3.pck outputs/3.pck

test1k: default
	./pa2 examples/1K.pr outputs/1K.po outputs/1K.dim outputs/1K.pck
